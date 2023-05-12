/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:28:40 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:19 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		result;
	va_list	pargs;
	t_list	*record;

	record = NULL;
	result = ft_parser(&record, (char *)format);
	if (result > -1)
	{
		va_start(pargs, format);
		ft_printer(pargs, record, &result);
		va_end(pargs);
	}
	ft_lstclear(&record, ft_del_info);
	return (result);
}

int	ft_parser(t_list **record, char *format)
{
	int		error;
	t_info	*field;

	error = 0;
	while (*format)
	{
		field = malloc(sizeof(t_info));
		if (field == NULL)
			return (-1);
		ft_field_init(field);
		if (*format != '%')
			error = ft_parse_text(field, record, &format);
		else if (*format == '%')
		{
			format = format + 1;
			ft_parse_flags(field, &format);
			error = ft_parse_width(field, &format, error);
			error = ft_parse_percision(field, &format, error);
			error = ft_parse_type(field, record, &format, error);
		}
		if (error == -1)
			break ;
	}
	return (error);
}

void	ft_printer(va_list pargs, t_list *record, int *result)
{
	t_info	*field;

	while (record)
	{
		field = record->content;
		if (field->type == TEXT)
			ft_print_text(field, result);
		else if (field->type == CHAR)
			ft_print_char(pargs, field, result);
		else if (field->type == STR)
			ft_print_str(pargs, field, result);
		else if (field->type == PTR)
			ft_print_ptr(pargs, field, result);
		else if (field->type == SINT)
			ft_print_sint(pargs, field, result);
		else if (field->type == UINT)
			ft_print_uint(pargs, field, result);
		else if (field->type == LHEX)
			ft_print_lhex(pargs, field, result);
		else if (field->type == UHEX)
			ft_print_uhex(pargs, field, result);
		else if (field->type == PERCENT)
			ft_print_percent(field, result);
		record = record->next;
	}
}

void	ft_field_init(t_info *field)
{
	field->start = NULL;
	field->end = NULL;
	field->flags = ALL_OFF;
	field->width = 0;
	field->precision = -1;
	field->type = NONE;
}

void	ft_del_info(void *field)
{
	free(field);
	field = NULL;
}
