/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:14:58 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 20:05:55 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_pl(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_plane	*plane;
	double	denom;
	double	nom;

	plane = (t_plane *)obj;
	rec->normal = unit_vector(plane->vec);
	if (dot(rec->normal, ray->direction) > 0.0)
		rec->normal = scala_mul(rec->normal, -1);
	denom = dot(rec->normal, ray->direction);
	if (fabs(denom) > EPSILON)
	{
		nom = dot(vector_sub(plane->coord, ray->origin), rec->normal);
		rec->t = nom / denom;
		if (rec->t < T_MIN || rec->t > t_max)
			return (false);
		rec->p = ray_at(ray, rec->t);
		rec->color = plane->color;
		rec->obj = obj;
		rec->texture = plane->texture;
	}
	return (true);
}
