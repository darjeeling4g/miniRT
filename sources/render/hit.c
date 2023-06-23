/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:43:21 by siyang            #+#    #+#             */
/*   Updated: 2023/06/23 20:46:50 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_hit(bool (*fp[4])(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec))
{
	fp[SP] = hit_sp;
	fp[PL] = hit_pl;
	fp[CY] = hit_cy;
	fp[CO] = hit_co;
}

bool	hit_obj(t_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_hit_fp		hit[4];
	bool			is_hit;
	t_hit_record	temp_rec;
	double			closest_so_far;

	init_hit(hit);
	is_hit = false;
	closest_so_far = t_max;
	while (obj)
	{
		if (hit[obj->id](obj, ray, closest_so_far, &temp_rec))
		{
			is_hit = true;
			closest_so_far = temp_rec.t;
			rec->p = temp_rec.p;
			rec->normal = temp_rec.normal;
			rec->t = temp_rec.t;
			rec->color = temp_rec.color;
			rec->obj = temp_rec.obj;
			rec->texture = temp_rec.texture;
		}
		obj = obj->next;
	}
	return (is_hit);
}
