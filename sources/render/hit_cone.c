/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:15:05 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 20:07:40 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_co(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_cone		*cone;
	double		a;
	double		b;
	double		c;
	t_point3	vertex;
	double		cosine;
	t_vec3		cp;
	double		base;

	cone = (t_cone *)obj;
	base = hit_co_base(cone, ray, t_max, rec);
	base = -1;
	cosine = cos(atan2(cone->diameter / 2.0, cone->height));
	vertex = vector_sub(cone->base_center, scala_mul(cone->vec, cone->height));

	a = dot(ray->direction, ray->direction) * pow(cosine, 2.0) - pow(dot(ray->direction, cone->vec), 2.0);
	
	b = 2 * dot(vector_sub(ray->origin, vertex), ray->direction) * pow(cosine, 2.0) \
	- 2 * dot(ray->direction, cone->vec) * dot(vector_sub(ray->origin, vertex), cone->vec);
	
	c = dot(vector_sub(ray->origin, vertex), vector_sub(ray->origin, vertex)) \
	* pow(cosine, 2.0) - pow(dot(vector_sub(ray->origin, vertex), cone->vec), 2.0);

	rec->t = get_root(a, b, c, t_max);
	cp = vector_add(vector_sub(ray->origin, vertex), scala_mul(ray->direction, rec->t));
	if (dot(cp, cone->vec) > cone->height || dot(unit_vector(cp), cone->vec) < 0.0)
		rec->t = -1;
	if (rec->t == -1 && base == -1)
		return (false);
	else if ((base != -1 && base < rec->t) || (base != -1 && rec->t == -1))
	{
		rec->t = base;
		return (true);
	}
	rec->p = ray_at(ray, rec->t);
	rec->normal = unit_vector(vector_sub(cp, scala_mul(cone->vec, length(cp) / cosine)));
	if (dot(ray->direction, rec->normal) > 0.0)
		rec->normal = scala_mul(rec->normal, -1);
	rec->color = cone->color;
	rec->texture = NONE;
	return (true);
}

double	hit_co_base(t_cone *cone, t_ray *ray, double t_max, t_hit_record *rec)
{
	double 		denom;
	double		nom;
	double		r;

	rec->normal = cone->vec;
	if (dot(rec->normal, ray->direction) > 0.0)
		rec->normal = scala_mul(rec->normal, -1);
	denom = dot(rec->normal, ray->direction);
	if (fabs(denom) > EPSILON)
	{
		nom = dot(vector_sub(cone->base_center, ray->origin), rec->normal);
		rec->t = nom / denom;
		rec->p = ray_at(ray, rec->t);
		rec->color = cone->color;
		rec->texture = NONE;
		r = length(vector_sub(ray_at(ray, rec->t), cone->base_center));
		if (r > cone->diameter / 2.0)
			return (-1);
		if (rec->t > T_MIN && rec->t < t_max)
			return (rec->t);
	}
	return (-1);
}
