/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:15:02 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 13:23:02 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_cy(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_cylinder	*cylinder;
	double		surface;
	double		top;
	double		bottom;
	t_vec3		cp;

	cylinder = (t_cylinder *)obj;
	surface = hit_cy_surface(cylinder, ray, t_max);
	top = hit_cy_base(cylinder, ray, t_max, true);
	bottom = hit_cy_base(cylinder, ray, t_max, false);

	if (surface == -1 && top == -1 && bottom == -1)
		return (false);
	else if (surface == -1)
	{
		rec->t = top;
		if (top == -1)
			rec->t = bottom;
		else if (bottom != -1 && top > bottom)
			rec->t = bottom;
	}
	else
	{
		rec->t =surface;
		if (top != -1 && top < surface)
			rec->t = top;
		else if (bottom != -1 && bottom < surface)
			rec->t = bottom;
	}
	rec->p = ray_at(ray, rec->t);
	if (rec->t == surface)
	{
		cp = vector_sub(rec->p, vector_sub(cylinder->coord, scala_mul(cylinder->vec, cylinder->height / 2.0)));
		rec->normal = unit_vector(vector_sub(cp, scala_mul(cylinder->vec, dot(cp, cylinder->vec))));
	}
	else if (rec->t == top)
		rec->normal = unit_vector(cylinder->vec);
	else if (rec->t == bottom)
		rec->normal = scala_mul(unit_vector(cylinder->vec), -1);
	if (dot(ray->direction, rec->normal) > 0.0)
		rec->normal = scala_mul(rec->normal, -1);
	rec->color = cylinder->color;
	rec->obj = obj;
//	rec->texture = NONE;
	rec->texture = CHECKER;
//	rec->texture = BUMP;
	return (true);
}

double	hit_cy_base(t_cylinder *cy, t_ray *ray, double t_max, bool is_top)
{
	t_point3	c;
	double		r;
	double		denom;
	double		t;

	if (is_top == true)
		c = vector_add(cy->coord, scala_mul(cy->vec, cy->height / 2.0));
	else
		c = vector_sub(cy->coord, scala_mul(cy->vec, cy->height / 2.0));
	denom = dot(ray->direction, cy->vec);
	if (fabs(denom) < EPSILON)
		return (-1);
	t = dot(vector_sub(c, ray->origin), cy->vec) / denom;
	if (t < T_MIN || t > t_max)
		return (-1);
	r = length(vector_sub(ray_at(ray, t), c));
	if (r > cy->diameter / 2.0)
		return (-1);
	return (t);
}

double	hit_cy_surface(t_cylinder *cy, t_ray *ray, double t_max)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;
	t_point3	p;
	t_vec3		ce;
	t_vec3		cp;

	ce = vector_sub(ray->origin, vector_sub(cy->coord, scala_mul(cy->vec, cy->height / 2.0)));
	a = dot(ray->direction, ray->direction) - pow(dot(ray->direction, cy->vec), 2.0);
	b = 2.0 * (dot(ce, ray->direction) - dot(ray->direction, cy->vec) * dot(ce, cy->vec));
	c = dot(ce, ce) - pow(dot(ce, cy->vec), 2.0) - pow((cy->diameter / 2.0), 2.0);
	
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < EPSILON)
		return (-1);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / (2.0 * a);
	if (root < T_MIN || root > t_max)
	{
		root = (-b + sqrtd) / (2.0 * a);
		if (root < T_MIN || root > t_max)
			return (-1);
	}
	p = ray_at(ray, root);
	cp = vector_sub(p, vector_sub(cy->coord, scala_mul(cy->vec, cy->height / 2.0)));
	if (dot(cp, cy->vec) < 0.0 || dot(cp, cy->vec) > cy->height)
		return (-1);
	return (root);
}
