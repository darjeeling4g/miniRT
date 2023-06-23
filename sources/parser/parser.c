/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:00 by siyang            #+#    #+#             */
/*   Updated: 2023/06/23 20:50:05 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parser(int fd, t_scene *scene)
{
	char	*line;
	int		id;
	void	(*fp[7])(t_scene *, char *);
	int		check_overlap[2];
	char	*tmp;

	init_parser(fp);
	ft_bzero(check_overlap, sizeof(int) * 2);
	while (true)
	{
		line = get_next_line(fd);
		tmp = line;
		if (line == NULL)
			return ;
		if (*line != '\n')
		{
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
		free(tmp);
	}
}

void	init_parser(void (*fp[7])(t_scene *, char *))
{
	fp[SP] = sp_parser;
	fp[PL] = pl_parser;
	fp[CY] = cy_parser;
	fp[CO] = co_parser;
	fp[A] = a_parser;
	fp[C] = c_parser;
	fp[L] = l_parser;
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
