/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_tbn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:17:02 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 13:34:10 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tbn	get_tbn(t_hit_record *rec)
{
	t_tbn		tbn;
	t_vec3		t;
	t_vec3		b;
	t_cylinder	*cylinder;

	ft_bzero(&tbn, sizeof(t_tbn));
	if (rec->obj->id == SP)
	{
		t = unit_vector(cross(vec3(0.0, 1.0, 0.0), rec->normal));
		b = unit_vector(cross(rec->normal, t));
		tbn = tangent_space(t, b, rec->normal);
	}
	else if (rec->obj->id == CY)
	{
		cylinder = (t_cylinder *)rec->obj;
		b = cross(cylinder->vec, rec->normal);
		if (length(b) < EPSILON)
			tbn = tangent_space(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), \
					rec->normal);
		else
			tbn = tangent_space(cylinder->vec, unit_vector(b), rec->normal);
	}
	return (tbn);
}

t_tbn	tangent_space(t_vec3 tangent, t_vec3 bitangent, t_vec3 normal)
{
	t_tbn	tbn;

	tbn.t = tangent;
	tbn.b = bitangent;
	tbn.n = normal;
	return (tbn);
}
