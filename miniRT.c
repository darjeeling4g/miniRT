/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:58:39 by siyang            #+#    #+#             */
/*   Updated: 2023/05/19 14:53:57 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_scene	scene;
	
	fd = open(argv[1], O_RDONLY);
	parser(fd, &scene);

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

	// mlx init
	// render
	exit(0);
}

void	error_exit(char *msg, int code)
{
	perror(msg);
	exit(code);
}
