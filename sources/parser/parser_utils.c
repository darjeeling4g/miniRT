/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daewoole <daewoole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:58:47 by siyang            #+#    #+#             */
/*   Updated: 2023/06/28 13:04:17 by daewoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_type	get_texture(char **line)
{
	while (**line == ' ')
		(*line)++;
	if (!ft_strncmp(*line, "checker\n", 9))
		return (CHECKER);
	else if (!ft_strncmp(*line, "bump\n", 6))
		return (BUMP);
	else
		return (NONE);
}

double	get_float(char **line)
{
	double	res;

	while (**line == ' ')
		(*line)++;
	if (!validate_argument(*line))
		error_exit("Error\n: Invalid line", 1);
	res = ft_atof(*line);
	while ((**line >= '0' && **line <= '9') || **line == '.' || **line == '-')
		(*line)++;
	return (res);
}

t_color3	get_color(char **line)
{
	double	temp[3];
	double	value;
	int		i;

	while (**line == ' ')
		(*line)++;
	i = 0;
	while (i < 3)
	{
		if (!validate_argument(*line))
			error_exit("Error\n: Invalid line", 1);
		value = (double)ft_atoi(*line);
		if (value < 0 || value > 255)
			error_exit("Error\n: Invalid color value", 1);
		temp[i] = value / 255.0;
		while (**line >= '0' && **line <= '9')
			(*line)++;
		if (**line == ',')
			(*line)++;
		i++;
	}
	return (color3(temp[0], temp[1], temp[2]));
}

int	get_fov(char **line)
{
	int	res;

	while (**line == ' ')
		(*line)++;
	if (!validate_argument(*line))
		error_exit("Error\n: Invalid line", 1);
	res = ft_atoi(*line);
	if (res < 0 || res > 180)
		error_exit("Error\n: value of fov must be less \
		than 180 and larger than 0", 1);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	return (res);
}

t_vec3	get_vector(char **line, int flag)
{
	t_vec3	vec;
	double	temp[3];
	int		i;

	while (**line == ' ')
		(*line)++;
	i = 0;
	while (i < 3)
	{
		if (!validate_argument(*line))
			error_exit("Error\n: Invalid line", 1);
		temp[i] = ft_atof(*line);
		if (flag == DIRECTION && (temp[i] < -1.0 || temp[i] > 1.0))
			error_exit("Error\n: direction value must be in range [-1,1]", 1);
		while ((**line >= '0' && **line <= '9') \
				|| **line == '.' || **line == '-' || **line == '+')
			(*line)++;
		if (**line == ',')
			(*line)++;
		i++;
	}
	vec.x = temp[0];
	vec.y = temp[1];
	vec.z = temp[2];
	return (vec);
}
