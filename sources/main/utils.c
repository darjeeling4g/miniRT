/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:35:44 by siyang            #+#    #+#             */
/*   Updated: 2023/05/25 18:29:56 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg, int code)
{
	perror(msg);
	exit(code);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

t_point3	ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, scala_mul(ray->direction, t)));
}
