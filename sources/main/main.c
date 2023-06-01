/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/06/01 18:53:43 by siyang           ###   ########.fr       */
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
	init(&scene, &screen);
	render(&scene, &screen);
	mlx_hook(screen.win_ptr, 2, 0, key_hook, &scene);
	mlx_loop(screen.mlx_ptr);
	exit(EXIT_SUCCESS);
}

void init(t_scene *scene, t_screen *screen)
{
	screen->mlx_ptr = mlx_init();
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	screen->img.ptr = mlx_new_image(screen->mlx_ptr, WIDTH, HEIGHT);
	screen->img.addr = mlx_get_data_addr(screen->img.ptr, \
		&screen->img.bits_per_pixel, &screen->img.line_size, &screen->img.endian);
	screen->resolution = 1;
	scene->screen = screen;
	scene->lighting = true;
	scene->samples = 1;
}

