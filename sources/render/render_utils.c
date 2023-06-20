/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:10:43 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 19:10:45 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
