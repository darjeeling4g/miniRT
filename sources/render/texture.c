/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:37:17 by siyang            #+#    #+#             */
/*   Updated: 2023/06/17 22:54:39 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	checker_mapping(t_texture t, t_color3 color, int width, int height)
{
	int	u_int;
	int	v_int;

	u_int = t.u * width;
	v_int = t.v * height;
	if ((u_int + v_int) % 2 == 0)
		return (vector_sub(color3(1.0, 1.0, 1.0), color));
	else
		return (color);
}

t_vec3	bump_mapping(t_texture t, int width, int height)
{
	int	u_int;
	int	v_int;
	double sines;

	u_int = t.u * width;
	v_int = t.v * height;
	sines = sin(t.u * PI* 2) + sin(t.v * PI * 2) + sin(t.u * PI) + sin(t.v * PI);
	return (vec3(random_double(sines), random_double(sines), random_double(sines)));
}

t_texture	get_spherical_map(t_point3 point)
{
	t_texture	res;
	double		theta;
	double		phi;

	theta = acos(-point.y);
	phi = atan2(point.x, -point.z);
	res.u = phi / (2 * PI) + 0.5;
	res.v = theta / PI;
	return (res);
}

t_texture	get_planar_map(t_point3 point)
{
	t_texture	res;

	res.u = fmod(point.x, 1.0);
	if (res.u < 0.0)
		res.u = 1.0 + res.u;
	res.v = fmod(point.z, 1.0);
	if (res.v < 0.0)
		res.v = 1.0 + res.v;
	return (res);
}

t_texture	get_cylindrical_map(t_point3 point, double height)
{
	t_texture	res;
	double		phi;

	phi = atan2(point.x, -point.z);
	res.u = phi / (2 * PI) + 0.5;
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
