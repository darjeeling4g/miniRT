/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/25 17:44:04 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_scene	scene;
	
	if (argc != 2)
		error_exit("Error: invalid argument", 1);
	fd = open(argv[1], O_RDONLY);
	parser(fd, &scene);

	printf("===========ambient=============\n");
	printf("ratio : %lf\n", scene.a.ratio);
	printf("color : %d\n", scene.a.color);
	printf("===========camera=============\n");
	printf("coord => x: %lf y: %lf z: %lf\n", scene.c.coord.x, scene.c.coord.y, scene.c.coord.z);
	printf("vec => x: %lf y: %lf z: %lf\n", scene.c.vec.x, scene.c.vec.y, scene.c.vec.z);
	printf("fov : %d\n", scene.c.fov);
	printf("===========light=============\n");
	while (scene.l_lst)
	{
		printf("ratio : %lf\n", scene.l_lst->ratio);
		printf("coord => x: %lf y: %lf z: %lf\n", scene.l_lst->coord.x, scene.l_lst->coord.y, scene.l_lst->coord.z);
		printf("color : %d\n", scene.l_lst->color);
		scene.l_lst = (t_light *)scene.l_lst->next;
	}
	printf("===========sphere=============\n");
	while (scene.sp_lst)
	{
		printf("%lf %lf %lf %lf %d\n", scene.sp_lst->coord.x, scene.sp_lst->coord.y, scene.sp_lst->coord.z, scene.sp_lst->diameter, scene.sp_lst->color);
		scene.sp_lst = (t_sphere *)scene.sp_lst->next;
	}
	printf("===========plane=============\n");
	while (scene.pl_lst)
	{
		printf("%lf %lf %lf %lf %lf %lf %d\n", scene.pl_lst->coord.x, scene.pl_lst->coord.y, scene.pl_lst->coord.z, scene.pl_lst->vec.x, scene.pl_lst->vec.y, scene.pl_lst->vec.z, scene.pl_lst->color);
		scene.pl_lst = (t_plane *)scene.pl_lst->next;
	}
	printf("===========cylinder=============\n");
	while (scene.cy_lst)
	{
		printf("%lf %lf %lf %lf %lf %lf %lf %lf %d\n", scene.cy_lst->coord.x, scene.cy_lst->coord.y, scene.cy_lst->coord.z, scene.cy_lst->vec.x, scene.cy_lst->vec.y, scene.cy_lst->vec.z, scene.cy_lst->diameter, scene.cy_lst->height, scene.cy_lst->color);
		scene.cy_lst = (t_cylinder *)scene.cy_lst->next;
	}

	t_screen	screen;

	init(&screen);	
	// render
	render(&scene, &screen);
	mlx_put_image_to_window(screen.mlx_ptr, screen.win_ptr, screen.img.ptr, 0, 0);
	mlx_loop(screen.mlx_ptr);
	exit(0);
}

void	init(t_screen *screen)
{
	// mlx init
	screen->mlx_ptr = mlx_init();
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	screen->img.ptr = mlx_new_image(screen->mlx_ptr, WIDTH, HEIGHT);
	screen->img.addr = mlx_get_data_addr(screen->img.ptr, &screen->img.bits_per_pixel, \
		&screen->img.line_size, &screen->img.endian);	
}

void	render(t_scene *scene, t_screen *screen)
{
	int	*pixel;
	int	color;
	int	x;
	int	y;

	/*
	double	viewport_height;
	double	viewport_width;
	double	aspect_ratio;
	double	focal_length;
	double	theta;
	double	h;
	double	horizontal[3];
	double	vertical[3];
	double	top_left_corner[3];
	t_ray	ray;

	// camera
	focal_length = 1.0;
	aspect_ratio = WIDTH / HEIGHT;
	theta = degrees_to_radians(scene->c.fov);
	h = tan(theta / 2) * focal_length;
	viewport_width = 2.0 * h;
	viewport_height = viewport_width / aspect_ratio;

	ray.origin[X] = scene->c.coord[X];
	ray.origin[Y] = scene->c.coord[Y];
	ray.origin[Z] = scene->c.coord[Z];

	horizontal[X] = viewport_width;
	horizontal[Y] = 0;
	horizontal[Z] = 0;

	vertical[X] = 0;
	vertical[Y] = viewport_height;
	vertical[Z] = 0;
	*/

	pixel = (int *)screen->img.addr;
	color = 0xff0000;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			*pixel = color;
			pixel = (int *)(screen->img.addr + (y * screen->img.line_size \
					+ (x * (screen->img.bits_per_pixel / 8))));
			x++;
		}
		y++;
	}
}

