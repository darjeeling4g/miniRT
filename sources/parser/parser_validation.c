/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:51 by siyang            #+#    #+#             */
/*   Updated: 2023/06/28 13:24:17 by daewoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	interpret_line(t_scene *scene, char *line, void \
(*fp[7])(t_scene *, char *), int *check_overlap)
{
	int		id;

	if (line == NULL)
	{
		validate_overlap(ERROR, check_overlap);
		return (1);
	}
	if (*line != '\n')
	{
		id = scan_id(line);
		if (id == ERROR)
			error_exit("Error\n: Invalid object id", 1);
		validate_overlap(id, check_overlap);
		if (id < A)
			line += 2;
		else
			line++;
		fp[id](scene, line);
	}
	return (0);
}

int	validate_argument(char *line)
{
	if (*line == '+')
		line++;
	else if (*line == '-')
		line++;
	if (!*line)
		return (0);
	while (*line)
	{
		if (*line == ',' || *line == ' ')
			break ;
		else if ((*line >= '0' && *line <= '9') \
				|| *line == '.' || *line == '\n')
			line++;
		else
			return (0);
	}
	return (1);
}

void	validate_overlap(int id, int *check_overlap)
{
	if ((id == A || id == C) && !check_overlap[id - 4])
		check_overlap[id - 4] = 1;
	else if ((id == A || id == C) && check_overlap[id - 4])
		error_exit("Error\n: A and C maximum number must be 1", 1);
	else if (id == ERROR && (check_overlap[0] == 0 || check_overlap[1] == 0))
		error_exit("Error\n: A and C must be more than 0", 1);
}
