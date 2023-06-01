/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:51:51 by siyang            #+#    #+#             */
/*   Updated: 2023/06/01 17:48:56 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_scene *scene, t_screen *screen)
{
	int			*pixel;
	int			x;
	int			y;
	int			i;
	int			j;
	int			k;
	double		u;
	double		v;
	t_ray		ray;
	t_color3	color;

	cam_init(scene);
	pixel = (int *)screen->img.addr;
	y = HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
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
			j = 0;
			while (j < screen->resolution)
			{
				k = 0;
				while (k < screen->resolution)
				{
					*pixel = write_color(color, (double)scene->samples);
					pixel = (int *)(screen->img.addr + (y * screen->img.line_size + \
						(x * (screen->img.bits_per_pixel / 8))));
					k++;
					x++;
				}
				j++;
				x -= screen->resolution;
				y--;
			}
			x += screen->resolution;
			y += screen->resolution;
		}
		y -= screen->resolution;
	}
}

int	write_color(t_color3 color, double samples)
{
	int res;
	int tmp[3];

	res = 0x0;
	tmp[0] = clamp(color.x / samples, 0.0, 1.0) * 255.0;
	tmp[1] = clamp(color.y / samples, 0.0, 1.0) * 255.0;
	tmp[2] = clamp(color.z / samples, 0.0, 1.0) * 255.0;
	res += tmp[0] << 16;
	res += tmp[1] << 8;
	res += tmp[2];
	return (res);
}

void	cam_init(t_scene *scene)
{
	double	theta;
	double	h;
	double	aspect_ratio;

	scene->c.w = unit_vector(scala_mul(scene->c.vec, -1));
	scene->c.u = unit_vector(cross(vec3(0.0, 1.0, 0.0), scene->c.w));
	scene->c.v = cross(scene->c.w, scene->c.u);

	scene->c.focal_length = 1.0;
	aspect_ratio = WIDTH / HEIGHT;
	theta = degrees_to_radians(scene->c.fov);
	h = tan(theta / 2.0) * scene->c.focal_length;
	scene->c.viewport_w = 2.0 * h;
	scene->c.viewport_h = scene->c.viewport_w / aspect_ratio;
	scene->c.horizontal = scala_mul(scene->c.u, scene->c.viewport_w);
	scene->c.vertical = scala_mul(scene->c.v, scene->c.viewport_h);
	scene->c.lower_left_corner = vector_sub(vector_sub(vector_sub(scene->c.coord, \
		scala_div(scene->c.horizontal, 2)), scala_div(scene->c.vertical, 2)), \
		scene->c.w);
}
