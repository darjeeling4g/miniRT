#include "minirt.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, double t_max, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;

	// 추후 최적화 예정 (짝수공식으로)
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(vector_sub(ray->origin, sphere->coord), ray->direction);
	c = dot(vector_sub(ray->origin, sphere->coord), vector_sub(ray->origin, sphere->coord)) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	root = (-b - sqrtd) / 2.0 * a;
	if (root < T_MIN || root > t_max)
	{
		root = (-b + sqrtd) / 2.0 * a;
		if (root < T_MIN || root > t_max)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = scala_div(vector_sub(rec->p, sphere->coord), sphere->radius);
	if (dot(ray->direction, rec->normal) < 0)
		rec->front_face = true;
	else
	{
		rec->front_face = false;
		rec->normal = scala_mul(rec->normal, -1);
	}
	return (true);
}
