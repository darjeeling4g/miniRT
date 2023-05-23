/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:59:14 by siyang            #+#    #+#             */
/*   Updated: 2023/05/18 17:55:17 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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
# include "get_next_line.h"
# include "generic_lst.h"

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
	t_generic_lst	*next;
	double			ratio;
	double			coord[3];
	int				color;
}	t_light;

typedef struct s_sphere
{
	t_generic_lst	*next;
	double			coord[3];
	double			diameter;
	int				color;
}	t_sphere;

typedef struct s_plane
{
	t_generic_lst	*next;
	double			coord[3];
	double			vec[3];
	int				color;
}	t_plane;

typedef struct s_cylinder
{
	t_generic_lst	*next;
	double			coord[3];
	double			vec[3];
	double			diameter;
	double			height;
	int				color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	a;
	t_camera	c;
	t_light		*l_lst;
	t_sphere	*sp_lst;
	t_plane		*pl_lst;
	t_cylinder	*cy_lst;
}	t_scene;

// miniRT.c
void	error_exit(char *msg, int code);

// ft_atof.c
double	ft_atof(const char *str);
double	make_double(const char *str, int *len);

// parser.c
void	parser(int fd, t_scene *scene);
void	init_parser(void (*fp[6])(t_scene *, char *));
int		scan_id(char *str);
void	a_parser(t_scene *scene, char *line);
void	c_parser(t_scene *scene, char *line);
void	l_parser(t_scene *scene, char *line);
void	sp_parser(t_scene *scene, char *line);
void	pl_parser(t_scene *scene, char *line);
void	cy_parser(t_scene *scene, char *line);

// parser_utils.c
double	get_float(char **line);
int		get_color(char **line);
int		get_fov(char **line);
void	get_coordinate(double *coord, char **line);
void	get_vector(double vec[3], char **line);

#endif