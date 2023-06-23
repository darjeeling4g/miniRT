/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:43:21 by siyang            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/22 21:47:57 by siyang           ###   ########.fr       */
=======
/*   Updated: 2023/06/23 16:11:42 by daewoole         ###   ########.fr       */
>>>>>>> 35f5236e8e03fb57d4521994b9070a3fae79e963
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
	bool			((*hit[4])(t_lst *, t_ray *, double, t_hit_record *));
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

