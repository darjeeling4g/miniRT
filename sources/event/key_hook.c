/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:30:45 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 22:20:53 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == EXIT)
		exit_hook(EXIT_SUCCESS);
	mode(keycode, scene);
	camera_move(keycode, &scene->c);
	camera_rotation(keycode, &scene->c);
	render(scene, scene->screen);
	return (0);
}

void	mode(int keycode, t_scene *scene)
{
	if (keycode == LIGHT)
	{
		if (scene->lighting == true)
			scene->lighting = false;
		else
			scene->lighting = true;
	}
	else if (keycode == RESOLUTION)
	{
		if (scene->screen->resolution == 1)
			scene->screen->resolution = 20;
		else
			scene->screen->resolution = 1;
	}
	else if (keycode == AA)
	{
		if (scene->samples == 1)
			scene->samples = 20;
		else
			scene->samples = 1;
	}
}

void	camera_move(int keycode, t_camera *camera)
{
	if (keycode == BACKWARD)
		camera->coord = vector_add(camera->coord, camera->w);
	else if (keycode == FORWARD)
		camera->coord = vector_sub(camera->coord, camera->w);
	else if (keycode == RIGHT)
		camera->coord = vector_add(camera->coord, camera->u);
	else if (keycode == LEFT)
		camera->coord = vector_sub(camera->coord, camera->u);
	else if (keycode == UP)
		camera->coord = vector_add(camera->coord, camera->v);
	else if (keycode == DOWN)
		camera->coord = vector_sub(camera->coord, camera->v);
}

void	camera_rotation(int keycode, t_camera *camera)
{
	double	angle;

	angle = degrees_to_radians(5.0);
	if (keycode == TILT_UP)
		camera->vec = rodrigues_formula(camera->vec, camera->u, angle);
	else if (keycode == TILT_DOWN)
		camera->vec = rodrigues_formula(camera->vec, camera->u, -angle);
	else if (keycode == PAN_LEFT)
		camera->vec = rodrigues_formula(camera->vec, camera->v, angle);
	else if (keycode == PAN_RIGHT)
		camera->vec = rodrigues_formula(camera->vec, camera->v, -angle);
}

t_vec3	rodrigues_formula(t_vec3 vec, t_vec3 axis, double angle)
{
	t_vec3	res;
	double	sin_theta;
	double	cos_theta;

	sin_theta = sin(angle);
	cos_theta = cos(angle);
	res.x = \
		(vec.x) * (cos_theta + (1 - cos_theta) * axis.x * axis.x) + \
		(vec.y) * ((1 - cos_theta) * axis.x * axis.y - sin_theta * axis.z) + \
		(vec.z) * ((1 - cos_theta) * axis.x * axis.z + sin_theta * axis.y);
	res.y = \
		(vec.x) * ((1 - cos_theta) * axis.y * axis.x + sin_theta * axis.z) + \
		(vec.y) * (cos_theta + (1 - cos_theta) * axis.y * axis.y) + \
		(vec.z) * ((1 - cos_theta) * axis.y * axis.z - sin_theta * axis.x);
	res.z = \
		(vec.x) * ((1 - cos_theta) * axis.z * axis.x - sin_theta * axis.y) + \
		(vec.y) * ((1 - cos_theta) * axis.z * axis.y + sin_theta * axis.x) + \
		(vec.z) * (cos_theta + (1 - cos_theta) * axis.z * axis.z);
	return (res);
}
