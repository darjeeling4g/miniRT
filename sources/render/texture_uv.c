/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:32:14 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 13:21:24 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_uv_map	get_uv_map(t_hit_record *rec)
{
	t_uv_map	uv;
	t_cylinder	*cylinder;
	t_point3	point;
	double		radius;

	ft_bzero(&uv, sizeof(t_uv_map));
	if (rec->obj->id == SP)
		uv = get_spherical_map(rec->normal);
	else if (rec->obj->id == PL)
		uv = get_planar_map(rec->p);
	else if (rec->obj->id == CY)
	{
		cylinder = (t_cylinder *)rec->obj;
		point = calibrate_cylinder(cylinder, rec->p);
		radius = cylinder->diameter / 2.0;
		uv = get_cylindrical_map(point, radius, cylinder->height);
	}
	return (uv);
}

t_uv_map	get_spherical_map(t_point3 point)
{
	t_uv_map	res;
	double		theta;
	double		phi;

	theta = acos(-point.y);
	phi = atan2(point.x, -point.z);
	res.u = phi / (2 * PI) + 0.5;
	res.v = theta / PI;
	return (res);
}

t_uv_map	get_planar_map(t_point3 point)
{
	t_uv_map	res;

	res.u = fmod(point.x, 1.0);
	if (res.u < 0.0)
		res.u = 1.0 + res.u;
	res.v = fmod(point.z, 1.0);
	if (res.v < 0.0)
		res.v = 1.0 + res.v;
	return (res);
}

t_uv_map	get_cylindrical_map(t_point3 point, double r, double height)
{
	t_uv_map	res;
	double		phi;

	(void) height;
	phi = atan2(point.x, -point.z);
	res.u = phi / (2 * PI) + 0.5;
	if (point.y < EPSILON)
		res.v = length(point) / r;
	else if (height - point.y < EPSILON)
		res.v = sqrt(length_squared(point) - pow(height, 2.0)) / r;
	else
		res.v = point.y / (height + EPSILON);
	return (res);
}

t_point3	calibrate_cylinder(t_cylinder *cylinder, t_point3 point)
{
	double	theta;
	t_vec3	rotate_axis;

	point = vector_sub(point, cylinder->coord);
	theta = acos(cylinder->vec.y);
	if (theta > EPSILON)
	{
		rotate_axis = unit_vector(cross(cylinder->vec, vec3(0.0, 1.0, 0.0)));
		point = rodrigues_formula(point, rotate_axis, theta);
	}
	point.y += cylinder->height / 2.0;
	return (point);
}
