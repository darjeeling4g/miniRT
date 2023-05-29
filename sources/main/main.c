/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/29 22:06:05 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int argc, char *argv[])
{
	int fd;
	t_scene scene;
	t_screen screen;

	if (argc != 2)
		error_exit("Error: invalid argument", 1);
	fd = open(argv[1], O_RDONLY);
	parser(fd, &scene);
	init(&screen);
	render(&scene, &screen);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr, screen.img.ptr, 0, 0);
	mlx_loop(screen.mlx_ptr);
	exit(EXIT_SUCCESS);
}

void init(t_screen *screen)
{
	// mlx init
	screen->mlx_ptr = mlx_init();
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	screen->img.ptr = mlx_new_image(screen->mlx_ptr, WIDTH, HEIGHT);
	screen->img.addr = mlx_get_data_addr(screen->img.ptr, &screen->img.bits_per_pixel,
										 &screen->img.line_size, &screen->img.endian);
}

int write_color(t_color3 color)
{
	int res;
	int tmp[3];

	res = 0;
	tmp[0] = clamp(((color.x / SAMPLES) + 1.0) * 0.5, 0.0, 1.0) * 255.0;
	tmp[1] = clamp(((color.y / SAMPLES) + 1.0) * 0.5, 0.0, 1.0) * 255.0;
	tmp[2] = clamp(((color.z / SAMPLES) + 1.0) * 0.5, 0.0, 1.0) * 255.0;
	res += tmp[0] << 16;
	res += tmp[1] << 8;
	res += tmp[2];
	return (res);
}

t_color3 ray_color(t_generic_lst *obj_lst, t_ray *ray)
{
	t_hit_record rec;

	if (hit_obj(obj_lst, ray, &rec))
		return (rec.normal);
	return (color3(1.0, 1.0, 1.0));
}

void cam_init(t_scene *scene)
{
	double theta;
	double h;
	double aspect_ratio;

	scene->c.focal_length = 1.0;
	aspect_ratio = WIDTH / HEIGHT;
	theta = degrees_to_radians(scene->c.fov);
	h = tan(theta / 2) * scene->c.focal_length;
	scene->c.viewport_w = 2.0 * h;
	scene->c.viewport_h = scene->c.viewport_w / aspect_ratio;
	scene->c.horizontal = vec3(scene->c.viewport_w, 0, 0);
	scene->c.vertical = vec3(0, scene->c.viewport_h, 0);
	scene->c.lower_left_corner = vector_sub(vector_sub(vector_sub(scene->c.coord, scala_div(scene->c.horizontal, 2)),
													   scala_div(scene->c.vertical, 2)),
											vec3(0, 0, scene->c.focal_length));
}

t_ray get_ray(t_camera cam, double u, double v)
{
	t_ray ray;

	ray.origin = cam.coord;
	ray.direction = vector_sub(vector_add(vector_add(cam.lower_left_corner,
													 scala_mul(cam.horizontal, u)),
										  scala_mul(cam.vertical, v)),
							   ray.origin);
	return (ray);
}

void render(t_scene *scene, t_screen *screen)
{
	int *pixel;
	int x;
	int y;
	t_ray ray;
	double u;
	double v;
	int i;
	t_color3 color;

	cam_init(scene);
	pixel = (int *)screen->img.addr;
	y = HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			i = 0;
			color = color3(0.0, 0.0, 0.0);
			while (i < SAMPLES)
			{
				u = (double)(x + random_double(i)) / (WIDTH - 1);				// 0 ~ 1
				v = (double)(HEIGHT - y - 1 + random_double(i)) / (HEIGHT - 1); // 0 ~ 1
				ray = get_ray(scene->c, u, v);
				color = vector_add(color, ray_color(scene->obj_lst, &ray));
				i++;
			}
			// *pixel = ray_color(scene->obj_lst, &ray);
			*pixel = write_color(color);
			pixel = (int *)(screen->img.addr + (y * screen->img.line_size + (x * (screen->img.bits_per_pixel / 8))));
			x++;
		}
		y--;
	}
}