/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:59:23 by daewoole          #+#    #+#             */
/*   Updated: 2023/06/23 15:59:24 by daewoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_root(t_lst *obj, t_ray *ray, double t_max)
{
	double	*coef;

	coef = get_coef(obj, ray);
	return (calc_discriminant(coef[0], coef[1], coef[2], t_max));
}

double*	get_coef(t_lst *obj, t_ray *ray)
{
	double	*coef;
	
	coef = NULL;
	if (obj->id == SP)
		coef = get_coef_sp(obj, ray);
	else if (obj->id == CO)
		coef = get_coef_co(obj, ray);
	return (coef);
}

double*	get_coef_co(t_lst *obj, t_ray *ray)
{
	t_cone		*cone;
	double		*coef;

	cone = (t_cone *)obj;
	coef = (double*)malloc(sizeof(double) * 3);
	coef[0] = dot(ray->direction, ray->direction) * pow(get_cosine(cone), 2.0) \
	- pow(dot(ray->direction, cone->vec), 2.0);
	coef[1] = 2 * dot(vector_sub(ray->origin,  get_vertex(cone)), ray->direction) * pow(get_cosine(cone), 2.0) \
	- 2 * dot(ray->direction, cone->vec) * dot(vector_sub(ray->origin,  get_vertex(cone)), cone->vec);	
	coef[2] = dot(vector_sub(ray->origin,  get_vertex(cone)), vector_sub(ray->origin,  get_vertex(cone))) \
	* pow(get_cosine(cone), 2.0) - pow(dot(vector_sub(ray->origin,  get_vertex(cone)), cone->vec), 2.0);
	return (coef);
}

double*	get_coef_sp(t_lst *obj, t_ray *ray)
{
	t_sphere	*sphere;
	double		*coef;

	sphere = (t_sphere *)obj;
	coef = (double*)malloc(sizeof(double) * 3);
	coef[0] = dot(ray->direction, ray->direction);
	coef[1] = 2.0 * dot(vector_sub(ray->origin, sphere->coord), ray->direction);
	coef[2] = dot(vector_sub(ray->origin, sphere->coord), \
	vector_sub(ray->origin, sphere->coord)) - sphere->radius * sphere->radius;
	return (coef);
}

double	calc_discriminant(double a, double b, double c, double t_max)
{
	double		discriminant;
	double		sqrtd;
	double		root;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1);
	sqrtd = sqrt(discriminant);
	if (a < 0.0 && b > 0.0)
		root = (-b + sqrtd) / (2.0 * a);
	else
		root = (-b - sqrtd) / (2.0 * a);
	if (root < T_MIN || root > t_max)
	{
		if (a < 0.0 && b > 0.0)
			root = (-b - sqrtd) / (2.0 * a);
		else
			root = (-b + sqrtd) / (2.0 * a);
		if (root < T_MIN || root > t_max)
			return (-1);
	}
	return (root);
}
