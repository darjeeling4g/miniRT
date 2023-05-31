/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/31 22:09:36 by siyang           ###   ########.fr       */
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
}

int	key_hook(int keycode, t_scene *scene)
{
	mode(keycode, scene);
	camera_move(keycode, &scene->c);
//	camera_ratate(keycode, &scene->c);
	render(scene, scene->screen);
	mlx_put_image_to_window(scene->screen->mlx_ptr, scene->screen->win_ptr, scene->screen->img.ptr, 0, 0);
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

