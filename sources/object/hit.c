#include "minirt.h"

void	init_hit(bool (*fp[3])(t_generic_lst *obj, t_ray *ray, double t_max, t_hit_record *rec))
{
	fp[0] = hit_sphere;
	// fp[1] = hit_plane;
	// fp[2] = hit_cylinder;
}

bool	hit_obj(t_generic_lst *obj, t_ray *ray, t_hit_record *rec)
{
	bool			(*hit[3])(t_generic_lst *, t_ray *, double, t_hit_record *);
	bool			is_hit;
	t_hit_record	temp_rec;
	double			closest_so_far;

	init_hit(hit);
	is_hit = false;
	closest_so_far = T_MAX;
	while (obj)
	{
		if (hit[obj->id](obj, ray, closest_so_far, &temp_rec))
		{
			is_hit = true;
			closest_so_far = temp_rec.t;
			rec->p = temp_rec.p;
			rec->normal = temp_rec.normal;
			rec->t = temp_rec.t;
			rec->front_face = temp_rec.front_face;
		}
		obj = obj->next;
	}
	return (is_hit);
}

bool	hit_sphere(t_generic_lst *obj, t_ray *ray, double t_max, t_hit_record *rec)
{
	t_sphere	*sphere;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;

	// 추후 최적화 예정 (짝수공식으로)
	sphere = (t_sphere *)obj;
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(vector_sub(ray->origin, sphere->coord), ray->direction);
	c = dot(vector_sub(ray->origin, sphere->coord), vector_sub(ray->origin, sphere->coord)) - sphere->radius * sphere->radius;
	discriminant = b * b - 4.0 * a * c;
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