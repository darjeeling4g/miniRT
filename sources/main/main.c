/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/06/01 17:56:23 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int argc, char *argv[])
{
	int			fd;
	t_scene		scene;
	t_screen	screen;

	if (argc != 2)
		error_exit("Error: invalid argument", 1);
	fd = open(argv[1], O_RDONLY);
	parser(fd, &scene);
	init(&screen);
	scene.screen = &screen;
	scene.lighting = true;
	scene.samples = 1;
	render(&scene, &screen);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr, screen.img.ptr, 0, 0);
	mlx_string_put(screen.mlx_ptr, screen.win_ptr, 10, 20, 0x228b22, \
		"[MODE] 1(Light ON & OFF) | 2(Resolution High & Low) | 3(Anti-aliasing)");
	mlx_string_put(screen.mlx_ptr, screen.win_ptr, 10, 50, 0x228b22, \
		"[MOVE] W(forward) | S(backward) | A(left) | D(right) | Q(up) | R(down)");
	mlx_string_put(screen.mlx_ptr, screen.win_ptr, 10, 80, 0x228b22, \
		"[ROTATION] Up(tilt-up) | Down(tilt-down) | Left(pan-left) | Right(pan-right)");
	mlx_hook(screen.win_ptr, 2, 0, key_hook, &scene);
	mlx_loop(screen.mlx_ptr);
	exit(EXIT_SUCCESS);
}

void init(t_screen *screen)
{
	screen->mlx_ptr = mlx_init();
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	screen->img.ptr = mlx_new_image(screen->mlx_ptr, WIDTH, HEIGHT);
	screen->img.addr = mlx_get_data_addr(screen->img.ptr, \
		&screen->img.bits_per_pixel, &screen->img.line_size, &screen->img.endian);
	screen->resolution = 1;
}

int	key_hook(int keycode, t_scene *scene)
{
	mode(keycode, scene);
	camera_move(keycode, &scene->c);
	camera_rotation(keycode, &scene->c);
	render(scene, scene->screen);
	mlx_put_image_to_window(scene->screen->mlx_ptr, scene->screen->win_ptr, scene->screen->img.ptr, 0, 0);
	mlx_string_put(scene->screen->mlx_ptr, scene->screen->win_ptr, 10, 20, 0x228b22, \
		"[MODE] 1(Light ON & OFF) | 2(Resolution High & Low) |3(Anti-aliasing)");
	mlx_string_put(scene->screen->mlx_ptr, scene->screen->win_ptr, 10, 50, 0x228b22, \
		"[MOVE] W(forward) | S(backward) | A(left) | D(right) | Q(up) | R(down)");
	mlx_string_put(scene->screen->mlx_ptr, scene->screen->win_ptr, 10, 80, 0x228b22, \
		"[ROTATION] Up(tilt-up) | Down(tilt-down) | Left(pan-left) | Right(pan-right)");
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
	if (keycode == TILT_UP)
		camera->vec = rodrigues_formula(camera->vec, camera->u, 5);
	else if (keycode == TILT_DOWN)
		camera->vec = rodrigues_formula(camera->vec, camera->u, -5);
	else if (keycode == PAN_LEFT)
		camera->vec = rodrigues_formula(camera->vec, camera->v, 5);
	else if (keycode == PAN_RIGHT)
		camera->vec = rodrigues_formula(camera->vec, camera->v, -5);
}

t_vec3	rodrigues_formula(t_vec3 vec, t_vec3 axis, double angle)
{
	t_vec3	res;
	double	sin_theta;
	double	cos_theta;

	sin_theta = sin(degrees_to_radians(angle));
	cos_theta = cos(degrees_to_radians(angle));
	res.x = (vec.x) * (cos_theta + (1 - cos_theta) * axis.x * axis.x) + \
			(vec.y) * ((1 - cos_theta) * axis.x * axis.y - sin_theta * axis.z) + \
			(vec.z) * ((1 - cos_theta) * axis.x * axis.z + sin_theta * axis.y);
    res.y = (vec.x) * ((1 - cos_theta) * axis.y * axis.x + sin_theta * axis.z) + \
			(vec.y) * (cos_theta + (1 - cos_theta) * axis.y * axis.y) + \
			(vec.z) * ((1 - cos_theta) * axis.y * axis.z - sin_theta * axis.x);
    res.z = (vec.x) * ((1 - cos_theta) * axis.z * axis.x - sin_theta * axis.y) + \
			(vec.y) * ((1 - cos_theta) * axis.z * axis.y + sin_theta * axis.x) + \
			(vec.z) * (cos_theta + (1 - cos_theta) * axis.z * axis.z);
	return (res);
}
