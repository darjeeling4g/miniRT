/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:51:51 by siyang            #+#    #+#             */
/*   Updated: 2023/06/21 20:06:00 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_scene *scene, t_screen *screen)
{
	int			x;
	int			y;
	t_color3	color;

	camera_init(&scene->c);
	y = HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_pixel_color(scene, x, y);
			draw_pixel(screen, color, x, y);
			x += screen->resolution;
		}
		y -= screen->resolution;
	}
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, \
		screen->img.ptr, 0, 0);
	mlx_string_put(screen->mlx_ptr, screen->win_ptr, 10, 20, 0x228b22, \
	"[MODE] 1(Light ON & OFF) | 2(Resolution High & Low) | 3(Anti-aliasing)");
	mlx_string_put(screen->mlx_ptr, screen->win_ptr, 10, 50, 0x228b22, \
	"[MOVE] W(forward) | S(backward) | A(left) | D(right) | Q(up) | E(down)");
	mlx_string_put(screen->mlx_ptr, screen->win_ptr, 10, 80, 0x228b22, \
	"[ROT] Up(tilt-up) | Down(tilt-down) | Left(pan-left) | Right(pan-right)");
}

t_color3	get_pixel_color(t_scene *scene, int x, int y)
{
	t_color3	color;
	t_ray		ray;
	int			i;
	double		u;
	double		v;

	color = color3(0.0, 0.0, 0.0);
	i = 0;
	while (i < scene->samples)
	{
		u = (double)(x + random_double(i)) / (WIDTH - 1);
		v = (double)(HEIGHT - y - 1 + random_double(i)) / (HEIGHT - 1);
		ray = get_ray(scene->c, u, v);
		color = vector_add(color, ray_color(scene, &ray));
		i++;
	}
	color = scala_div(color, scene->samples);
	return (color);
}

void	draw_pixel(t_screen *screen, t_color3 color, int x, int y)
{
	int	*pixel;
	int	i;
	int	j;

	i = -1;
	while (++i < screen->resolution)
	{
		j = -1;
		while (++j < screen->resolution)
		{
			pixel = (int *)(screen->img.addr + (y * screen->img.line_size + \
				(x * (screen->img.bpp / 8))));
			*pixel = write_color(color);
			x++;
		}
		x -= screen->resolution;
		y--;
	}
}

int	write_color(t_color3 color)
{
	int	res;
	int	tmp[3];

	res = 0x0;
	tmp[0] = clamp(color.x, 0.0, 1.0) * 255.0;
	tmp[1] = clamp(color.y, 0.0, 1.0) * 255.0;
	tmp[2] = clamp(color.z, 0.0, 1.0) * 255.0;
	res += tmp[0] << 16;
	res += tmp[1] << 8;
	res += tmp[2];
	return (res);
}

void	camera_init(t_camera *camera)
{
	double	theta;
	double	h;
	double	aspect_ratio;

	camera->w = unit_vector(scala_mul(camera->vec, -1));
	camera->u = unit_vector(cross(vec3(0.0, 1.0, 0.0), camera->w));
	camera->v = cross(camera->w, camera->u);
	camera->focal_length = 1.0;
	aspect_ratio = WIDTH / HEIGHT;
	theta = degrees_to_radians(camera->fov);
	h = tan(theta / 2.0) * camera->focal_length;
	camera->viewport_w = 2.0 * h;
	camera->viewport_h = camera->viewport_w / aspect_ratio;
	camera->horizontal = scala_mul(camera->u, camera->viewport_w);
	camera->vertical = scala_mul(camera->v, camera->viewport_h);
	camera->lower_left_corner = vector_sub(vector_sub(vector_sub(camera->coord, \
		scala_div(camera->horizontal, 2)), scala_div(camera->vertical, 2)), \
		camera->w);
}
