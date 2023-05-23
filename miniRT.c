/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/24 02:24:57 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_scene	scene;
	
	fd = open(argv[1], O_RDONLY);
	parser(fd, &scene);

/* 파싱  테스트
	printf("===========ambient=============\n");
	printf("ratio : %lf\n", scene.a.ratio);
	printf("color : %d\n", scene.a.color);
	printf("===========camera=============\n");
	printf("coord => x: %lf y: %lf z: %lf\n", scene.c.coord[0], scene.c.coord[1], scene.c.coord[2]);
	printf("vec => x: %lf y: %lf z: %lf\n", scene.c.vec[0], scene.c.vec[1], scene.c.vec[2]);
	printf("fov : %d\n", scene.c.fov);
	printf("===========light=============\n");
	while (scene.l_lst)
	{
		printf("ratio : %lf\n", scene.l_lst->ratio);
		printf("coord => x: %lf y: %lf z: %lf\n", scene.l_lst->coord[0], scene.l_lst->coord[1], scene.l_lst->coord[2]);
		printf("color : %d\n", scene.l_lst->color);
		scene.l_lst = scene.l_lst->next;
	}
	printf("===========sphere=============\n");
	while (scene.sp_lst)
	{
		printf("%lf %lf %lf %lf %d\n", scene.sp_lst->coord[0], scene.sp_lst->coord[1], scene.sp_lst->coord[2], scene.sp_lst->diameter, scene.sp_lst->color);
		scene.sp_lst = scene.sp_lst->next;
	}
	printf("===========plane=============\n");
	while (scene.pl_lst)
	{
		printf("%lf %lf %lf %lf %lf %lf %d\n", scene.pl_lst->coord[0], scene.pl_lst->coord[1], scene.pl_lst->coord[2], scene.pl_lst->vec[0], scene.pl_lst->vec[1], scene.pl_lst->vec[2], scene.pl_lst->color);
		scene.pl_lst = scene.pl_lst->next;
	}
	printf("===========cylinder=============\n");
	while (scene.cy_lst)
	{
		printf("%lf %lf %lf %lf %lf %lf %lf %lf %d\n", scene.cy_lst->coord[0], scene.cy_lst->coord[1], scene.cy_lst->coord[2], scene.cy_lst->vec[0], scene.cy_lst->vec[1], scene.cy_lst->vec[2], scene.cy_lst->diameter, scene.cy_lst->height, scene.cy_lst->color);
		scene.cy_lst = scene.cy_lst->next;
	}
*/
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

	pixel = screen->img.addr;
	color = 0xff0000;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			*pixel = color;
			pixel = screen->img.addr + (y * screen->img.line_size + (x * (screen->img.bits_per_pixel / 8)));
			x++;
		}
		y++;
	}
}

void	error_exit(char *msg, int code)
{
	perror(msg);
	exit(code);
}

double *vector_add(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] + vec2[0];
	vec[1] = vec1[1] + vec2[1];
	vec[2] = vec1[2] + vec2[2];
	return (vec);
}

double *vector_sub(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] - vec2[0];
	vec[1] = vec1[1] - vec2[1];
	vec[2] = vec1[2] - vec2[2];
	return (vec);
}

double *scala_mul(double scala, double *vec1)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = scala * vec1[0];
	vec[1] = scala * vec1[1];
	vec[2] = scala * vec1[2];
	return (vec);
}

double *scala_div(double scala, double *vec1)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[0] / scala;
	vec[1] = vec1[1] / scala;
	vec[2] = vec1[2] / scala;
	return (vec);
}

double length(double *vec) 
{
	return (sqrt(length_squared(vec)));
}

double length_squared(double *vec)
{
	return (vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

double	dot(double *vec1, double *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

double *cross(double *vec1, double *vec2)
{
	double	*vec;

	vec = (double*)malloc(sizeof(double) * 3);
	if (!vec)
		error_exit("Memory Allocation Failed", 1);
	vec[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	vec[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	vec[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return (vec);
}