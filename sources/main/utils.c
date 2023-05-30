/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:35:44 by siyang            #+#    #+#             */
/*   Updated: 2023/05/30 14:42:53 by siyang           ###   ########.fr       */
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

double random_double(int seed)
{
	return (((seed * RANDOM_A + RANDOM_C) % RANDOM_M) / (RAND_MAX + 1.0));
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
