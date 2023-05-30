/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:55:04 by siyang            #+#    #+#             */
/*   Updated: 2023/05/30 17:30:05 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	phong_lighting(t_scene *scene, t_hit_record rec)
{
	t_color3	result;
	t_color3	ambient;

	result = color3(0.0, 0.0, 0.0);
	ambient = scala_mul(scene->a.color, scene->a.ratio);
	result = vector_clamp(vector_add(result, vector_mul(ambient, rec.color)), 0.0, 1.0);
	return (result);
}
