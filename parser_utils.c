/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:47 by siyang            #+#    #+#             */
/*   Updated: 2023/05/24 02:56:10 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double get_float(char **line)
{
	double res;

	while (**line == ' ')
		(*line)++;
	if (!validate_argument(*line))
		error_exit("Parsing Error", 1);
	res = ft_atof(*line);
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
	return (res);
}

int get_color(char **line)
{
	int res;
	int value;
	int i;

	res = 0;
	while (**line == ' ')
		(*line)++;
	i = 2;
	while (i >= 0)
	{
		if (!validate_argument(*line))
			error_exit("Parsing Error", 1);
		value = ft_atoi(*line);
		if (value < 0 || value > 255)
			error_exit("Parsing Error", 1);
		res += (value << 8 * i);
		while (**line >= '0' && **line <= '9')
			(*line)++;
		if (**line == ',')
			(*line)++;
		i--;
	}
	return (res);
}

int get_fov(char **line)
{
	int res;

	while (**line == ' ')
		(*line)++;
	if (!validate_argument(*line))
		error_exit("Parsing Error", 1);
	res = ft_atoi(*line);
	if (res < 0 || res > 180)
		error_exit("Parsing Error", 1);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	return (res);
}

void get_coordinate(double *coord, char **line)
{
	int i;

	while (**line == ' ')
		(*line)++;
	i = 0;
	while (i < 3)
	{
		if (!validate_argument(*line))
			error_exit("Parsing Error", 1);
		coord[i] = ft_atof(*line);
		while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-' || **line == '+')
			(*line)++;
		if (**line == ',')
			(*line)++;
		i++;
	}
}

void get_vector(double vec[3], char **line)
{
	int i;

	while (**line == ' ')
		(*line)++;
	i = 0;
	while (i < 3)
	{
		if (!validate_argument(*line))
			error_exit("Parsing Error", 1);
		if (vec[i] < -1.0 || vec[i] > 1.0)
			error_exit("Parsing Error", 1);
		vec[i] = ft_atof(*line);
		while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-' || **line == '+')
			(*line)++;
		if (**line == ',')
			(*line)++;
		i++;
	}
}

int validate_argument(char *line)
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
		else if ((*line >= '0' && *line <= '9') || *line == '.' || *line == '\n')
			line++;
		else
			return (0);
	}
	return (1);
}
