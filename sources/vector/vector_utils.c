/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:26:53 by siyang            #+#    #+#             */
/*   Updated: 2023/05/31 16:01:50 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point3	point3(double x, double y, double z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color3	color3(double x, double y, double z)
{
	t_color3	color;

	color.x = x;
	color.y = y;
	color.z = z;
	return (color);

}
void	vector_set(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

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

double	length(t_vec3 vec)
{
	return (sqrt(length_squared(vec)));
}

double	length_squared(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	dot(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec);
}

t_vec3	unit_vector(t_vec3 vec)
{
	return (scala_div(vec, length(vec)));
}

t_vec3	reflect(t_vec3 vec, t_vec3 normal)
{
	return (vector_sub(scala_mul(normal, dot(vec, normal) * 2.0), vec));
}
