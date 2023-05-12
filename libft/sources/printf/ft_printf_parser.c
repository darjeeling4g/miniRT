/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:07:38 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:27 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_text(t_info *field, t_list **record, char **format)
{
	t_list	*new;

	field->type = TEXT;
	field->start = *format;
	while (**format != '%' && **format != 0)
		*format += 1;
	field->end = *format;
	new = ft_lstnew(field);
	if (new == NULL)
	{
		free(field);
		return (-1);
	}
	ft_lstadd_back(record, new);
	return (0);
}

void	ft_parse_flags(t_info *field, char **format)
{
	while (**format)
	{
		if (**format == '-')
			field->flags = field->flags | MINUS_ON;
		else if (**format == '+')
			field->flags = field->flags | PLUS_ON;
		else if (**format == ' ')
			field->flags = field->flags | BLANK_ON;
		else if (**format == '0')
			field->flags = field->flags | ZERO_ON;
		else if (**format == '#')
			field->flags = field->flags | HASH_ON;
		else
			break ;
		*format += 1;
	}
}

int	ft_parse_width(t_info *field, char **format, int error)
{
	char	*ptr;
	int		num;

	if (error == -1)
		return (-1);
	if (**format >= '1' && **format <= '9')
	{
		num = 0;
		ptr = *format;
		while (**format >= '0' && **format <= '9')
		{
			*format += 1;
			num++;
		}
		num = ft_atoi(ptr);
		if (num == 2147483647 || num < 0)
			return (-1);
		field->width = num;
	}
	return (0);
}

int	ft_parse_percision(t_info *field, char **format, int error)
{
	char	*ptr;
	int		num;

	if (error == -1)
		return (-1);
	if (**format == '.')
	{
		*format += 1;
		if (**format >= '0' && **format <= '9')
		{
			num = 0;
			ptr = *format;
			while (**format >= '0' && **format <= '9')
			{
				*format += 1;
				num++;
			}
			num = ft_atoi(ptr);
			field->precision = num;
		}
		else
			field->precision = 0;
	}
	return (0);
}

int	ft_parse_type(t_info *field, t_list **record, char **format, int error)
{
	t_list	*new;
	char	*types;
	char	*type;

	if (error == -1)
		return (-1);
	if (**format == 'i')
		field->type = SINT;
	else
	{
		types = "cspduxX%";
		type = ft_strchr(types, **format);
		if (type == NULL)
			return (-1);
		field->type = type - types + 2;
	}
	new = ft_lstnew(field);
	if (new == NULL)
	{
		free(field);
		return (-1);
	}
	ft_lstadd_back(record, new);
	*format += 1;
	return (0);
}
