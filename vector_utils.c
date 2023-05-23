/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:26:53 by siyang            #+#    #+#             */
/*   Updated: 2023/05/24 02:49:21 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*vector_add(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] + vec2[0];
	vec[1] = vec1[1] + vec2[1];
	vec[2] = vec1[2] + vec2[2];
	return (vec);
}

double	*vector_sub(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] - vec2[0];
	vec[1] = vec1[1] - vec2[1];
	vec[2] = vec1[2] - vec2[2];
	return (vec);
}

double	*scala_mul(double scala, double *vec1)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = scala * vec1[0];
	vec[1] = scala * vec1[1];
	vec[2] = scala * vec1[2];
	return (vec);
}

double	*scala_div(double scala, double *vec1)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] / scala;
	vec[1] = vec1[1] / scala;
	vec[2] = vec1[2] / scala;
	return (vec);
}

double	length(double *vec) 
{
	return (sqrt(length_squared(vec)));
}

double	length_squared(double *vec)
{
	return (vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

double	dot(double *vec1, double *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

double	*cross(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	vec[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	vec[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return (vec);
}

double	*ray_at(t_ray *ray, double t)
{
	double	*vec;
	double	*scaled_vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	scaled_vec = scala_mul(t, ray->direction);
	vec = vector_add(ray->origin, scaled_vec);
	free(scaled_vec);
	return (vec);
}