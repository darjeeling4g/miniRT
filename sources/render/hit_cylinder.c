/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:15:02 by siyang            #+#    #+#             */
/*   Updated: 2023/06/23 19:07:15 by daewoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_cy(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_cylinder	*cy;
	t_type		surface;

	cy = (t_cylinder *)obj;
	surface = select_type(hit_cy_base(cy, ray, t_max, true), \
		hit_cy_base(cy, ray, t_max, false), hit_cy_side(cy, ray, t_max), rec);
	if (surface == NONE)
		return (false);
	set_cy_rec(cy, ray, rec, surface);
	return (true);
}

void	set_cy_rec(t_cylinder *cy, t_ray *ray, t_hit_record *rec, int surface)
{
	t_vec3	cp;

	rec->p = ray_at(ray, rec->t);
	if (surface == SIDE)
	{
		cp = vector_sub(rec->p, vector_sub(cy->coord, \
			scala_mul(cy->vec, cy->height / 2.0)));
		rec->normal = unit_vector(vector_sub(cp, \
			scala_mul(cy->vec, dot(cp, cy->vec))));
	}
	else if (surface == TOP)
		rec->normal = unit_vector(cy->vec);
	else if (surface == BOTTOM)
		rec->normal = scala_mul(unit_vector(cy->vec), -1);
	if (dot(ray->direction, rec->normal) > 0.0)
		rec->normal = scala_mul(rec->normal, -1);
	rec->color = cy->color;
	rec->obj = (t_lst *)cy;
	rec->texture = cy->texture;
}

t_type	select_type(double top, double bottom, double side, t_hit_record *rec)
{
	if (side == -1 && top == -1 && bottom == -1)
		return (NONE);
	else if (side == -1)
	{
		rec->t = top;
		if (top == -1)
			rec->t = bottom;
		else if (bottom != -1 && top > bottom)
			rec->t = bottom;
	}
	else
	{
		rec->t = side;
		if (top != -1 && top < side)
			rec->t = top;
		else if (bottom != -1 && bottom < side)
			rec->t = bottom;
	}
	if (rec->t == top)
		return (TOP);
	else if (rec->t == bottom)
		return (BOTTOM);
	else
		return (SIDE);
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

double	hit_cy_side(t_cylinder *cy, t_ray *ray, double t_max)
{
	double		root;
	t_point3	p;
	t_vec3		cp;

	root = get_root((t_lst*)cy, ray, t_max);
	if (root == -1)
		return (-1);
	p = ray_at(ray, root);
	cp = vector_sub(p, vector_sub(cy->coord, \
			scala_mul(cy->vec, cy->height / 2.0)));
	if (dot(cp, cy->vec) < 0.0 || dot(cp, cy->vec) > cy->height)
		return (-1);
	return (root);
}
