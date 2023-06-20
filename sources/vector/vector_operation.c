/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:17:05 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 18:17:25 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vector_add(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vec3	vector_sub(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vec3	vector_mul(t_vec3 vec1, t_vec3 vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

t_vec3	scala_mul(t_vec3 vec, double scala)
{
	vec.x *= scala;
	vec.y *= scala;
	vec.z *= scala;
	return (vec);
}

t_vec3	scala_div(t_vec3 vec, double scala)
{
	vec.x /= scala;
	vec.y /= scala;
	vec.z /= scala;
	return (vec);
}
