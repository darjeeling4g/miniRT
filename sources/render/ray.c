/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:42:14 by siyang            #+#    #+#             */
/*   Updated: 2023/06/21 20:06:55 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point3	ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, scala_mul(ray->direction, t)));
}

t_color3	ray_color(t_scene *scene, t_ray *ray)
{
	t_hit_record	rec;
	t_vec3			unit_vec;
	double			t;

	if (hit_obj(scene->obj_lst, ray, T_MAX, &rec))
	{
		texture_mapping(&rec, &scene->screen->bump);
		return (phong_lighting(scene, rec, *ray));
	}
	unit_vec = unit_vector(ray->direction);
	t = 0.5 * (unit_vec.y + 1.0);
	return (vector_add(scala_mul(color3(1.0, 1.0, 1.0), 1.0 - t), \
		scala_mul(color3(0.5, 0.7, 1.0), t)));
}

t_ray	get_ray(t_camera cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam.coord;
	ray.direction = vector_sub(vector_add(vector_add(cam.lower_left_corner, \
		scala_mul(cam.horizontal, u)), scala_mul(cam.vertical, v)), ray.origin);
	return (ray);
}
