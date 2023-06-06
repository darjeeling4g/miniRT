/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:37:17 by siyang            #+#    #+#             */
/*   Updated: 2023/06/06 10:54:46 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	checker_mapping(t_texture t, t_color3 color, int width, int height)
{
	int	u_int;
	int	v_int;

	u_int = t.u * width;
	v_int = t.v * height;
	if ((u_int + v_int) % 2 == 0)
		return (color3(1.0, 1.0, 1.0));
	else
		return (color);
}

t_texture	get_spherical_map(t_point3 point)
{
	t_texture	res;
	double		theta;
	double		phi;

	theta = acos(-point.y);
	phi = atan2(point.x, -point.z);

	res.u = phi / (2 * PI) + 0.5;
	res.v = theta / PI;
	return (res);
}
