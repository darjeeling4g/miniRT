/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:55:04 by siyang            #+#    #+#             */
/*   Updated: 2023/05/30 19:59:02 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	phong_lighting(t_scene *scene, t_hit_record rec)
{
	t_color3	result;
	t_color3	ambient;
	t_light		*light;

	result = color3(0.0, 0.0, 0.0);
	light = scene->l_lst;
	while (light)
	{
		result = vector_add(result, point_light(*light, rec));
		light = (t_light *)light->next;
	}
	ambient = scala_mul(scene->a.color, scene->a.ratio);
	result = vector_add(result, ambient);
	result = vector_clamp(vector_mul(result, rec.color), 0.0, 1.0);
	return (result);
}

t_color3	point_light(t_light light, t_hit_record rec)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		diff;

	light_dir = unit_vector(vector_sub(light.coord, rec.p));
	diff = fmax(dot(rec.normal, light_dir), 0.0);
	diffuse =  scala_mul(light.color, diff);
	return (diffuse);
}
