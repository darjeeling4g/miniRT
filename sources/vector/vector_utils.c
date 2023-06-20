/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:26:53 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 18:18:14 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_set(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	length(t_vec3 vec)
{
	return (sqrt(length_squared(vec)));
}

double	length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3	unit_vector(t_vec3 vec)
{
	return (scala_div(vec, length(vec)));
}

t_vec3	reflect(t_vec3 vec, t_vec3 normal)
{
	return (vector_sub(scala_mul(normal, dot(vec, normal) * 2.0), vec));
}
