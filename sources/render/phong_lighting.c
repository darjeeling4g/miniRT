/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:55:04 by siyang            #+#    #+#             */
/*   Updated: 2023/06/06 10:47:08 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	phong_lighting(t_scene *scene, t_hit_record rec, t_ray ray)
{
	t_color3	result;
	t_color3	ambient;
	t_light		*light;

	result = color3(0.0, 0.0, 0.0);
	if (scene->lighting == true)
	{
		light = scene->l_lst;
		while (light)
		{
			result = vector_add(result, point_light(scene->obj_lst, *light, rec, ray));
			light = (t_light *)light->next;
		}
	}
	ambient = scala_mul(scene->a.color, scene->a.ratio);
	result = vector_add(result, ambient);
	result = vector_clamp(vector_mul(result, rec.color), 0.0, 1.0);
	return (result);
}

t_color3	point_light(t_generic_lst *obj, t_light light, t_hit_record rec, t_ray ray)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		diff;

	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;

	double		brightness;

	if (in_shadow(obj, vector_add(rec.p, scala_mul(rec.normal, EPSILON)), vector_sub(light.coord, rec.p)))
		return (color3(0.0, 0.0, 0.0));

	light_dir = unit_vector(vector_sub(light.coord, rec.p));
	diff = fmax(dot(rec.normal, light_dir), 0.0);
	diffuse =  scala_mul(light.color, diff);

	view_dir = unit_vector(scala_mul(ray.direction, -1));
	reflect_dir = reflect(light_dir, rec.normal);
	spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), SPEC_SHININESS);
	specular = scala_mul(scala_mul(light.color, SPEC_STRENGTH), spec);

	brightness = light.ratio * LUMEN;

	return (scala_mul(vector_add(diffuse, specular), brightness));
}

bool	in_shadow(t_generic_lst *obj, t_point3 origin, t_vec3 direction)
{
	t_ray			shadow_ray;
	t_hit_record	temp;
	double			ray_len;

	shadow_ray.origin = origin;
	shadow_ray.direction = unit_vector(direction);
	ray_len = length(direction);
	if (hit_obj(obj, &shadow_ray, ray_len, &temp))
		return (true);
	return (false);
}
