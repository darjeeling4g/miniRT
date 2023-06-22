/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:37:17 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 13:31:18 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	texture_mapping(t_hit_record *rec, t_img *bump)
{
	t_uv_map	uv;
	t_tbn		tbn;
	int			width;
	int			height;

	if (rec->texture == CHECKER)
	{
		uv = get_uv_map(rec);
		get_checker_size(rec, &width, &height);
		rec->color = checker_mapping(uv, rec->color, width, height);
	}
	else if (rec->texture == BUMP)
	{
		uv = get_uv_map(rec);
		tbn = get_tbn(rec);
		rec->normal = bump_mapping(bump, uv, tbn);
	}
}

t_vec3	bump_mapping(t_img *bump, t_uv_map map, t_tbn tbn)
{
	int		x;
	int		y;
	int		*px;
	t_vec3	normal;
	t_vec3	res;

	x = map.u * bump->width;
	y = map.v * bump->height;
	px = (int *)(bump->addr + (y * bump->line_size + (x * (bump->bpp / 8))));
	normal = vec3((*px & 0xff0000) >> 16, (*px & 0xff00) >> 8, *px & 0xff);
	res.x = tbn.t.x * normal.x + tbn.b.x * normal.y + tbn.n.x * normal.z;
	res.y = tbn.t.y * normal.x + tbn.b.y * normal.y + tbn.n.y * normal.z;
	res.z = tbn.t.z * normal.x + tbn.b.z * normal.y + tbn.n.z * normal.z;
	return (unit_vector(res));
}

t_color3	checker_mapping(t_uv_map map, t_color3 color, int width, int height)
{
	int	u_int;
	int	v_int;

	u_int = map.u * width;
	v_int = map.v * height;
	if ((u_int + v_int) % 2 == 0)
		return (vector_sub(color3(1.0, 1.0, 1.0), color));
	else
		return (color);
}

void	get_checker_size(t_hit_record *rec, int *width, int *height)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	if (rec->obj->id == SP)
	{
		sphere = (t_sphere *)rec->obj;
		*height = sphere->radius * 10;
		*width = *height * 2;
	}
	else if (rec->obj->id == PL)
	{
		*width = 2;
		*height = 2;
	}
	else if (rec->obj->id == CY)
	{
		cylinder = (t_cylinder *)rec->obj;
		*width = cylinder->diameter * 4;
		*height = cylinder->height;
	}
}
