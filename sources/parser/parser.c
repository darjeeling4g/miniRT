/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:00 by siyang            #+#    #+#             */
/*   Updated: 2023/06/17 22:28:42 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parser(int fd, t_scene *scene)
{
	char	*line;
	int		id;
	void	(*fp[7])(t_scene *, char *);
	int		check_overlap[3];

	init_parser(fp);
	ft_bzero(check_overlap, sizeof(int) * 3);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		id = scan_id(line);
		validate_overlap(id, check_overlap);
		if (id == ERROR)
			error_exit("Parsing Error", 1);
		else if (id < A)
			line += 2;
		else
			line++;
		fp[id](scene, line);
	}
}

void	init_parser(void (*fp[7])(t_scene *, char *))
{
	fp[0] = sp_parser;
	fp[1] = pl_parser;
	fp[2] = cy_parser;
	fp[3] = co_parser;
	fp[4] = a_parser;
	fp[5] = c_parser;
	fp[6] = l_parser;
}

int	scan_id(char *str)
{
	int	id;

	id = ERROR;
	if (*str >= 'A' && *str <= 'Z' && *(str + 1) == ' ')
	{
		if (!ft_strncmp(str, "A", 1))
			id = A;
		else if (!ft_strncmp(str, "C", 1))
			id = C;
		else if (!ft_strncmp(str, "L", 1))
			id = L;
	}
	else if (*str >= 'a' && *str <= 'z' && *(str + 1) != ' ')
	{
		if (!ft_strncmp(str, "sp", 2))
			id = SP;
		else if (!ft_strncmp(str, "pl", 2))
			id = PL;
		else if (!ft_strncmp(str, "cy", 2))
			id = CY;
		else if (!ft_strncmp(str, "co", 2))
			id = CO;
	}
	return (id);
}

void	a_parser(t_scene *scene, char *line)
{
	scene->a.ratio = get_float(&line);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		error_exit("Parsing error", 1);
	scene->a.color = get_color(&line);
}

void	c_parser(t_scene *scene, char *line)
{
	scene->c.coord = get_coordinate(&line);
	scene->c.vec = get_vector(&line);
	scene->c.fov = get_fov(&line);
}

void	l_parser(t_scene *scene, char *line)
{
	t_light		*light;

	light = (t_light*)malloc(sizeof(t_light));
	if (!light)
		exit(EXIT_FAILURE);
	light->coord = get_coordinate(&line);
	light->ratio = get_float(&line);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		error_exit("Parsing error", 1);
	light->color = get_color(&line);
	light->next = NULL;
	gl_lstadd_back((t_generic_lst **)&(scene->l_lst), (t_generic_lst *)light);
}

void	sp_parser(t_scene *scene, char *line)
{
	t_sphere	*sp;

	sp = (t_sphere*)malloc(sizeof(t_sphere));
	if (!sp)
		exit(EXIT_FAILURE);
	sp->coord = get_coordinate(&line);
	sp->radius = get_float(&line) / 2.0;
	sp->color = get_color(&line);
	sp->next = NULL;
	sp->id = SP;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)sp);
}

void	pl_parser(t_scene *scene, char *line)
{
	t_plane	*pl;

	pl = (t_plane*)malloc(sizeof(t_plane));
	if (!pl)
		exit(EXIT_FAILURE);
	pl->coord = get_coordinate(&line);
	pl->vec = get_vector(&line);
	pl->color = get_color(&line);
	pl->next = NULL;
	pl->id = PL;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)pl);
}

void	cy_parser(t_scene *scene, char *line)
{
	t_cylinder	*cy;

	cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	if (!cy)
		exit(EXIT_FAILURE);
	cy->coord = get_coordinate(&line);
	cy->vec = unit_vector(get_vector(&line));
	cy->diameter = get_float(&line);
	cy->height = get_float(&line);
	cy->color = get_color(&line);
	cy->next = NULL;
	cy->id = CY;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)cy);
}

void	co_parser(t_scene *scene, char *line)
{
	t_cone	*co;

	co = (t_cone *)malloc(sizeof(t_cone));
	if (!co)
	{
		// printf("dsadsadsda\n");
		exit(EXIT_FAILURE);
		// printf("dsadsadsda\n");
	}
	co->base_center = get_coordinate(&line);
	co->vec = unit_vector(get_vector(&line));
	co->diameter = get_float(&line);
	co->height = get_float(&line);
	co->color = get_color(&line);
	co->next = NULL;
	co->id = CO;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)co);
}
