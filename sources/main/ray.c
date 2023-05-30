/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:42:14 by siyang            #+#    #+#             */
/*   Updated: 2023/05/30 14:56:08 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point3	ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, scala_mul(ray->direction, t)));
}

t_color3	ray_color(t_generic_lst *obj_lst, t_ray *ray)
{
	t_hit_record rec;

	if (hit_obj(obj_lst, ray, &rec))
		return (rec.normal);
	return (color3(1.0, 1.0, 1.0));
}

t_ray	get_ray(t_camera cam, double u, double v)
{
	t_ray ray;

	ray.origin = cam.coord;
	ray.direction = vector_sub(vector_add(vector_add(cam.lower_left_corner, \
		scala_mul(cam.horizontal, u)), scala_mul(cam.vertical, v)), ray.origin);
	return (ray);
}
