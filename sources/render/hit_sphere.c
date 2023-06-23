/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:14:54 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 13:26:35 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sp(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj;
	rec->t = get_root(obj, ray, t_max);
	if (rec->t == -1)
		 return (false);
	rec->p = ray_at(ray, rec->t);
	rec->normal = scala_div(vector_sub(rec->p, sphere->coord), sphere->radius);
	if (dot(ray->direction, rec->normal) > EPSILON)
		rec->normal = scala_mul(rec->normal, -1);
	rec->color = sphere->color;
	rec->obj = obj;
//	rec->texture = NONE;
	rec->texture = CHECKER;
//	rec->texture = BUMP;
	return (true);
}
