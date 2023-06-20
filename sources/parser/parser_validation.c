/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:51 by siyang            #+#    #+#             */
/*   Updated: 2023/06/20 18:04:55 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		error_exit("Parsing Error", 1);
}
