/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:59:14 by siyang            #+#    #+#             */
/*   Updated: 2023/05/31 14:54:07 by siyang           ###   ########.fr       */
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
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "generic_lst.h"
# include "vector.h"

# define ERROR -1

# define WIDTH 1600.0
# define HEIGHT 900.0
# define EPSILON 1e-6
# define T_MIN EPSILON
# define T_MAX HUGE_VAL
# define PI 3.1415926535897932385

# define RANDOM_A 1103515245
# define RANDOM_C 12345
# define RANDOM_M 2147483648

# define SAMPLES 20

# define SPEC_SHININESS 32
# define SPEC_STRENGTH 0.5
# define LUMEN 1

enum e_type
{
	SP,
	PL,
	CY,
	A,
	C,
	L
};

typedef struct s_ambient
{
	double		ratio;
	t_color3	color;
}	t_ambient;

typedef struct s_camera
{
	t_point3	coord;
	t_vec3		vec;
	int			fov;
	double		viewport_h;
	double		viewport_w;
	t_vec3		horizontal;
	t_vec3		vertical;
	double		focal_length;
	t_point3	lower_left_corner;
}	t_camera;

typedef struct s_light
{
	t_generic_lst	*next;
	double			ratio;
	t_point3		coord;
	t_color3		color;
}	t_light;

typedef struct s_sphere
{
	t_generic_lst	*next;
	int				id;
	t_point3		coord;
	double			radius;
	t_color3		color;
}	t_sphere;

typedef struct s_plane
{
	t_generic_lst	*next;
	int				id;
	t_point3		coord;
	t_vec3			vec;
	t_color3		color;
}	t_plane;

typedef struct s_cylinder
{
	t_generic_lst	*next;
	int				id;
	t_point3		coord;
	t_vec3			vec;
	double			diameter;
	double			height;
	t_color3		color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient		a;
	t_camera		c;
	t_light			*l_lst;
	t_generic_lst	*obj_lst;
}	t_scene;

typedef struct s_img {
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_screen;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		t;
	bool		front_face;
	t_color3	color;
}	t_hit_record;

// main.c
void	init(t_screen *screen);
void	render(t_scene *scene, t_screen *screen);

// utils.c
void	error_exit(char *msg, int code);
double	degrees_to_radians(double degrees);
double	random_double(int seed);
double	clamp(double x, double min, double max);
t_vec3	vector_clamp(t_vec3 vec, double min, double max);

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
double		get_float(char **line);
t_color3	get_color(char **line);
int			get_fov(char **line);
t_point3	get_coordinate(char **line);
t_vec3		get_vector(char **line);
int 		validate_argument(char *line);

// render.c
void	render(t_scene *scene, t_screen *screen);
int		write_color(t_color3 color);
void	cam_init(t_scene *scene);

// ray.c
t_point3	ray_at(t_ray *ray, double t);
t_color3	ray_color(t_scene *scene, t_ray *ray);
t_ray		get_ray(t_camera cam, double u, double v);

// hit.c
void	init_hit(bool (*fp[3])(t_generic_lst *obj, t_ray *ray, double t_max, t_hit_record *rec));
bool	hit_obj(t_generic_lst *obj, t_ray *ray, double t_max, t_hit_record *rec);
bool	hit_sphere(t_generic_lst *obj, t_ray *ray, double t_max, t_hit_record *rec);

// phong_lighting.c
t_color3	phong_lighting(t_scene *scene, t_hit_record rec, t_ray ray);
t_color3	point_light(t_generic_lst *obj, t_light light, t_hit_record rec, t_ray ray);
bool		in_shadow(t_generic_lst *obj, t_point3 origin, t_vec3 direction);

#endif
