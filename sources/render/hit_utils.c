/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:59:23 by daewoole          #+#    #+#             */
/*   Updated: 2023/06/23 19:22:01 by daewoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_root(t_lst *obj, t_ray *ray, double t_max)
{
	t_point3	coef;

	coef = vec3(0,0,0);
	if (obj->id == SP)
		coef = get_coef_sp(obj, ray);
	else if (obj->id == CO)
		coef = get_coef_co(obj, ray);
	else if (obj->id == CY)
		coef = get_coef_cy(obj, ray);
	return (calc_discriminant(coef.x, coef.y, coef.z, t_max));
}

t_point3	get_coef_cy(t_lst *obj, t_ray *ray)
{
	t_point3	coef;
	t_vec3		ce;
	t_cylinder	*cy;

	cy = (t_cylinder*)obj;
	ce = vector_sub(ray->origin, vector_sub(cy->coord, \
			scala_mul(cy->vec, cy->height / 2.0)));
	coef.x = dot(ray->direction, ray->direction) \
			- pow(dot(ray->direction, cy->vec), 2.0);
	coef.y = 2.0 * (dot(ce, ray->direction) \
			- dot(ray->direction, cy->vec) * dot(ce, cy->vec));
	coef.z = dot(ce, ce) - pow(dot(ce, cy->vec), 2.0) \
			- pow((cy->diameter / 2.0), 2.0);
	return (coef);
}

t_point3	get_coef_co(t_lst *obj, t_ray *ray)
{
	t_cone		*cone;
	t_point3	coef;

	cone = (t_cone *)obj;
	coef.x = dot(ray->direction, ray->direction) * pow(get_cosine(cone), 2.0) \
	- pow(dot(ray->direction, cone->vec), 2.0);
	coef.y = 2 * dot(vector_sub(ray->origin,  get_vertex(cone)), ray->direction) * pow(get_cosine(cone), 2.0) \
	- 2 * dot(ray->direction, cone->vec) * dot(vector_sub(ray->origin,  get_vertex(cone)), cone->vec);	
	coef.z = dot(vector_sub(ray->origin,  get_vertex(cone)), vector_sub(ray->origin,  get_vertex(cone))) \
	* pow(get_cosine(cone), 2.0) - pow(dot(vector_sub(ray->origin,  get_vertex(cone)), cone->vec), 2.0);
	return (coef);
}

t_point3	get_coef_sp(t_lst *obj, t_ray *ray)
{
	t_sphere	*sphere;
	t_point3	coef;

	sphere = (t_sphere *)obj;
	coef.x = dot(ray->direction, ray->direction);
	coef.y = 2.0 * dot(vector_sub(ray->origin, sphere->coord), ray->direction);
	coef.z = dot(vector_sub(ray->origin, sphere->coord), \
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
