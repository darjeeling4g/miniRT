/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:43:21 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 19:30:03 by siyang           ###   ########.fr       */
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
	bool			(*hit[4])(t_lst *, t_ray *, double, t_hit_record *);
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

double	get_root(double a, double b, double c, double t_max)
{
	double		discriminant;
	double		sqrtd;
	double		root;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1);
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / (2.0 * a);
	if (root < T_MIN || root > t_max)
	{
		root = (-b + sqrtd) / (2.0 * a);
		if (root < T_MIN || root > t_max)
			return (-1);
	}
	return (root);
}
