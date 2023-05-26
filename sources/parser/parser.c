/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:00 by siyang            #+#    #+#             */
/*   Updated: 2023/05/26 22:24:34 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parser(int fd, t_scene *scene)
{
	char	*line;
	int		id;
	void	(*fp[6])(t_scene *, char *);

	init_parser(fp);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		id = scan_id(line);
		if (id == ERROR)
			error_exit("Parsing Error", 1);
		else if (id < A)
			line += 2;
		else
			line++;
		fp[id](scene, line);
	}
}

void	init_parser(void (*fp[6])(t_scene *, char *))
{
	fp[0] = sp_parser;
	fp[1] = pl_parser;
	fp[2] = cy_parser;
	fp[3] = a_parser;
	fp[4] = c_parser;
	fp[5] = l_parser;
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
	}
	return (id);
}

void	a_parser(t_scene *scene, char *line)
{
	scene->a.ratio = get_float(&line);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		error_exit("Pasing error", 1);
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
		error_exit("Pasing error", 1);
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
	cy->vec = get_vector(&line);
	cy->diameter = get_float(&line);
	cy->height = get_float(&line);
	cy->color = get_color(&line);
	cy->next = NULL;
	cy->id = CY;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)cy);
}
