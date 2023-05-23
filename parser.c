/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:00 by siyang            #+#    #+#             */
/*   Updated: 2023/05/19 15:59:36 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		else if (id < SP)
			line++;
		else
			line += 2;
		fp[id](scene, line);
	}
}

void	init_parser(void (*fp[6])(t_scene *, char *))
{
	fp[0] = a_parser;
	fp[1] = c_parser;
	fp[2] = l_parser;
	fp[3] = sp_parser;
	fp[4] = pl_parser;
	fp[5] = cy_parser;
}

int	scan_id(char *str)
{
	int	id;

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
		if (!ft_strncmp(str, "pl", 2))
			id = PL;
		if (!ft_strncmp(str, "cy", 2))
			id = CY;
	}
	else
		id = ERROR;
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
	get_coordinate(scene->c.coord, &line);
	get_vector(scene->c.vec, &line);
	scene->c.fov = get_fov(&line);
}

void	l_parser(t_scene *scene, char *line)
{
	t_light		*light;

	light = malloc(sizeof(t_light));
	if (!light)
		exit(EXIT_FAILURE);
	get_coordinate(light->coord, &line);
	light->ratio = get_float(&line);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		error_exit("Pasing error", 1);
	light->color = get_color(&line);
	light->next = NULL;
	gl_lstadd_back(&(scene->l_lst), &light);
}

void	sp_parser(t_scene *scene, char *line)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		exit(EXIT_FAILURE);
	get_coordinate(sp->coord, &line);
	sp->diameter = get_float(&line);
	sp->color = get_color(&line);
	sp->next = NULL;
	gl_lstadd_back(&(scene->sp_lst), &sp);
}

void	pl_parser(t_scene *scene, char *line)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		exit(EXIT_FAILURE);
	get_coordinate(pl->coord, &line);
	get_vector(pl->vec, &line);
	pl->color = get_color(&line);
	pl->next = NULL;
	gl_lstadd_back(&(scene->pl_lst), &pl);
}

void	cy_parser(t_scene *scene, char *line)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		exit(EXIT_FAILURE);
	get_coordinate(cy->coord, &line);
	get_vector(cy->vec, &line);
	cy->diameter = get_float(&line);
	cy->height = get_float(&line);
	cy->color = get_color(&line);
	cy->next = NULL;
	gl_lstadd_back(&(scene->cy_lst), &cy);
}
