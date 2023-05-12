/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:47:43 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:35 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_text(t_info *field, int *result)
{
	char	*start;
	char	*end;

	if (*result != -1)
	{
		start = field->start;
		end = field->end;
		safe_write(1, start, end - start, result);
	}
}

void	ft_print_char(va_list pargs, t_info *field, int *result)
{
	char	c;

	c = (char)va_arg(pargs, int);
	if ((field->flags | MINUS_ON) != MINUS_ON || field->precision > 0)
		*result = -1;
	if (field->flags == ALL_OFF)
		ft_putchar_iter(' ', field->width - 1, result);
	safe_write(1, &c, 1, result);
	if (field->flags == MINUS_ON)
		ft_putchar_iter(' ', field->width - 1, result);
}

void	ft_print_str(va_list pargs, t_info *field, int *result)
{
	char	*s;
	int		len;

	s = (char *)va_arg(pargs, char *);
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if ((field->flags & PLUS_ON) || (field->flags & HASH_ON))
		*result = -1;
	if (len >= field->precision && field->precision > -1)
		len = field->precision;
	if (!(field->flags & MINUS_ON))
		ft_putchar_iter(' ', field->width - len, result);
	safe_write(1, s, len, result);
	if (field->flags == MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}

void	ft_print_ptr(va_list pargs, t_info *field, int *result)
{
	size_t	addr;
	char	array[19];
	int		i;
	int		len;

	addr = (size_t)va_arg(pargs, void *);
	i = ft_num_to_hex(addr, array, 1, 0);
	len = ft_strlen(&array[i]);
	if ((field->flags | MINUS_ON) != MINUS_ON)
		*result = -1;
	if (field->flags == ALL_OFF)
		ft_putchar_iter(' ', field->width - len, result);
	safe_write(1, &array[i], len, result);
	if (field->flags == MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}

void	ft_print_percent(t_info *field, int *result)
{
	if ((field->flags & MINUS_ZERO_ON) == MINUS_ZERO_ON)
		field->flags -= ZERO_ON;
	if (!(field->flags & MINUS_ON) && !(field->flags & ZERO_ON))
		ft_putchar_iter(' ', field->width - 1, result);
	if (field->flags & ZERO_ON)
		ft_putchar_iter('0', field->width - 1, result);
	safe_write(1, "%", 1, result);
	if (field->flags & MINUS_ON)
		ft_putchar_iter(' ', field->width - 1, result);
}
