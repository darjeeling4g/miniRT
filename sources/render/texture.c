/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:37:17 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 17:40:19 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	texture_mapping(t_hit_record *rec, t_img *bump)
{
	t_vec3		tangent;
	t_cylinder	*cylinder;

	if (rec->texture == CHECKER)
	{
		if (rec->obj->id == SP)
			rec->color = checker_mapping(get_spherical_map(rec->normal), rec->color, 20, 10);
		else if (rec->obj->id == PL)
			rec->color = checker_mapping(get_planar_map(rec->p), rec->color, 2, 2);
		else if (rec->obj->id == CY)
		{
			cylinder = (t_cylinder *)rec->obj;
			rec->color = checker_mapping(get_cylindrical_map(calibrate_cylinder(cylinder, rec->p), cylinder->height), \
				cylinder->color, cylinder->diameter * 4, cylinder->height);
		}
	}
	else if (rec->texture == BUMP)
	{
		if (rec->obj->id == SP)
		{
			tangent = unit_vector(cross(vec3(0.0, 1.0, 0.0), rec->normal));
			rec->normal = bump_mapping(bump, get_spherical_map(rec->normal), \
				get_tangent_space(tangent, unit_vector(cross(rec->normal, tangent)), rec->normal));
		}
		else if (rec->obj->id == CY)
		{
			cylinder = (t_cylinder *)rec->obj;
			rec->normal = bump_mapping(bump, get_cylindrical_map(calibrate_cylinder(cylinder, rec->p), cylinder->height), \
				get_tangent_space(cylinder->vec, unit_vector(cross(cylinder->vec, rec->normal)), rec->normal));
		}
		return ;
	}
}

t_vec3	bump_mapping(t_img *bump, t_uv_map map, t_tbn tbn)
{
	int		x;
	int		y;
	int		*pixel;
	t_vec3	normal;
	t_vec3	res;

	x = map.u * bump->width;
	y = map.v * bump->height;
	pixel = (int *)(bump->addr + (y * bump->line_size + (x * (bump->bpp / 8))));
	normal = vec3((*pixel & 0xff0000) >> 16, (*pixel & 0xff00) >> 8, *pixel & 0xff);
	res.x = tbn.t.x * normal.x + tbn.b.x * normal.y + tbn.n.x * normal.z;
	res.y = tbn.t.y * normal.x + tbn.b.y * normal.y + tbn.n.y * normal.z;
	res.z = tbn.t.z * normal.x + tbn.b.z * normal.y + tbn.n.z * normal.z;
	return (unit_vector(res));
}

t_tbn	get_tangent_space(t_vec3 tangent, t_vec3 bitangent, t_vec3 normal)
{
	t_tbn		tbn;

	tbn.t = tangent;
	tbn.b = bitangent;
	tbn.n = normal;
	return (tbn);
}

t_color3	checker_mapping(t_uv_map map, t_color3 color, int width, int height)
{
	int	u_int;
	int	v_int;

	u_int = map.u * width;
	v_int = map.v * height;
	if ((u_int + v_int) % 2 == 0)
		return (vector_sub(color3(1.0, 1.0, 1.0), color));
	else
		return (color);
}

t_uv_map	get_spherical_map(t_point3 point)
{
	t_uv_map	res;
	double	theta;
	double	phi;

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

t_uv_map	get_cylindrical_map(t_point3 point, double height)
{
	t_uv_map	res;
	double	phi;

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
