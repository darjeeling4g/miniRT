/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:04:38 by siyang            #+#    #+#             */
/*   Updated: 2023/06/22 20:04:13 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	l_parser(t_scene *scene, char *line)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		exit(EXIT_FAILURE);
	light->coord = get_coordinate(&line);
	light->ratio = get_float(&line);
	if (scene->a.ratio < 0.0 || scene->a.ratio > 1.0)
		error_exit("Parsing error", 1);
	light->color = get_color(&line);
	light->next = NULL;
	light->id = L;
	gl_lstadd_back((t_generic_lst **)&(scene->l_lst), (t_generic_lst *)light);
}

void	sp_parser(t_scene *scene, char *line)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		exit(EXIT_FAILURE);
	sp->coord = get_coordinate(&line);
	sp->radius = get_float(&line) / 2.0;
	sp->color = get_color(&line);
	sp->texture = get_texture(&line);
	sp->next = NULL;
	sp->id = SP;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)sp);
}

void	pl_parser(t_scene *scene, char *line)
{
	t_plane	*pl;

	pl = (t_plane *)malloc(sizeof(t_plane));
	if (!pl)
		exit(EXIT_FAILURE);
	pl->coord = get_coordinate(&line);
	pl->vec = get_vector(&line);
	pl->color = get_color(&line);
	pl->texture = get_texture(&line);
	pl->next = NULL;
	pl->id = PL;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)pl);
}

void	cy_parser(t_scene *scene, char *line)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		exit(EXIT_FAILURE);
	cy->coord = get_coordinate(&line);
	cy->vec = unit_vector(get_vector(&line));
	cy->diameter = get_float(&line);
	cy->height = get_float(&line);
	cy->color = get_color(&line);
	cy->texture = get_texture(&line);
	cy->next = NULL;
	cy->id = CY;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)cy);
}

void	co_parser(t_scene *scene, char *line)
{
	t_cone	*co;

	co = (t_cone *)malloc(sizeof(t_cone));
	if (!co)
		exit(EXIT_FAILURE);
	co->base_center = get_coordinate(&line);
	co->vec = unit_vector(get_vector(&line));
	co->diameter = get_float(&line);
	co->height = get_float(&line);
	co->color = get_color(&line);
	co->texture = get_texture(&line);
	co->next = NULL;
	co->id = CO;
	gl_lstadd_back(&(scene->obj_lst), (t_generic_lst *)co);
}
