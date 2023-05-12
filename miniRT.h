/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:59:14 by siyang            #+#    #+#             */
/*   Updated: 2023/05/12 20:18:12 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef
#define MINIRT_H

# include <fcntl.h>
// open
# include <unistd.h>
// close, read, write
# include <stdio.h>
// printf, perror, strerror
# include <stdlib.h>
// malloc, free, exit
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define ERROR -1

enum e_type
{
	A,
	C,
	L,
	SP,
	PL,
	CY	
};

typedef struct s_ambient
{
	double	ratio;
	int		color;
}	t_ambient;

typedef struct s_camera
{
	double	coord[3];
	double	vec[3];
	int		fov;
}	t_camera;

typedef struct s_light
{
	double	ratio;
	double	coord[3];
	int		color;
}	t_light;

typedef struct s_sphere
{
	double	coord[3];
	double	dia;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	double	coord[3];
	double	vec[3];
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	double	coord[3];
	double	vec[3];
	double	dia;
	double	height;
	int		color;
}	t_cylinder;

typedef struct s_scene
{
	struct s_ambient	a;
	struct s_camera		c;
	t_list				l_lst;
	t_list				sp_lst;
	t_list				pl_lst;
	t_list				cy_lst;
}	t_scene;

#endif
