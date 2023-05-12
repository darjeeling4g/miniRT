/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sub_printer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:07:21 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:58 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pre_masking(t_info *field, int *len, int num)
{
	if (field->type == SINT)
	{
		if ((field->flags & PLUS_BLANK_ON) == PLUS_BLANK_ON)
			field->flags -= BLANK_ON;
		if ((field->flags & PLUS_BLANK_ON) || num < 0)
			field->width -= 1;
	}
	else if (field->type == LHEX || field->type == UHEX)
	{
		if ((field->flags & HASH_ON) && num != 0)
			field->width -= 2;
	}
	if ((field->flags & MINUS_ZERO_ON) == MINUS_ZERO_ON)
		field->flags -= ZERO_ON;
	if ((field->flags & ZERO_ON) && (field->precision >= 0))
		field->flags -= ZERO_ON;
	if (field->precision > *len)
		field->width -= field->precision - *len;
	if (num == 0 && field->precision == 0)
		*len = 0;
}

void	ft_print_sint(va_list pargs, t_info *field, int *result)
{
	int		num;
	char	array[11];
	int		i;
	int		len;

	num = va_arg(pargs, int);
	i = ft_num_to_str(num, array);
	len = ft_strlen(&array[i]);
	if (field->flags & HASH_ON)
		*result = -1;
	pre_masking(field, &len, num);
	if (!(field->flags & MINUS_ON) && !(field->flags & ZERO_ON))
		ft_putchar_iter(' ', field->width - len, result);
	ft_putsign(field, num, result);
	if (field->flags & ZERO_ON)
		ft_putchar_iter('0', field->width - len, result);
	ft_putchar_iter('0', field->precision - len, result);
	safe_write(1, &array[i], len, result);
	if (field->flags & MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}

void	ft_print_uint(va_list pargs, t_info *field, int *result)
{
	unsigned int	num;
	char			array[11];
	int				i;
	int				len;

	num = va_arg(pargs, unsigned int);
	i = ft_unum_to_str(num, array);
	len = ft_strlen(&array[i]);
	if ((field->flags | MINUS_ZERO_ON) != MINUS_ZERO_ON)
		*result = -1;
	pre_masking(field, &len, num);
	if (!(field->flags & MINUS_ON) && !(field->flags & ZERO_ON))
		ft_putchar_iter(' ', field->width - len, result);
	if (field->flags & ZERO_ON)
		ft_putchar_iter('0', field->width - len, result);
	ft_putchar_iter('0', field->precision - len, result);
	safe_write(1, &array[i], len, result);
	if (field->flags & MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}

void	ft_print_lhex(va_list pargs, t_info *field, int *result)
{
	unsigned int	num;
	char			array[19];
	int				i;
	int				len;

	num = va_arg(pargs, unsigned int);
	i = ft_num_to_hex(num, array, 0, 0);
	len = ft_strlen(&array[i]);
	if (field->flags & PLUS_BLANK_ON)
		*result = -1;
	pre_masking(field, &len, num);
	if (!(field->flags & MINUS_ON) && !(field->flags & ZERO_ON))
		ft_putchar_iter(' ', field->width - len, result);
	if ((field->flags & HASH_ON) && num != 0)
		safe_write(1, "0x", 2, result);
	if (field->flags & ZERO_ON)
		ft_putchar_iter('0', field->width - len, result);
	ft_putchar_iter('0', field->precision - len, result);
	safe_write(1, &array[i], len, result);
	if (field->flags & MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}

void	ft_print_uhex(va_list pargs, t_info *field, int *result)
{
	unsigned int	num;
	char			array[19];
	int				i;
	int				len;

	num = va_arg(pargs, unsigned int);
	i = ft_num_to_hex(num, array, 0, 32);
	len = ft_strlen(&array[i]);
	if (field->flags & PLUS_BLANK_ON)
		*result = -1;
	pre_masking(field, &len, num);
	if (!(field->flags & MINUS_ON) && !(field->flags & ZERO_ON))
		ft_putchar_iter(' ', field->width - len, result);
	if ((field->flags & HASH_ON) && num != 0)
		safe_write(1, "0X", 2, result);
	if (field->flags & ZERO_ON)
		ft_putchar_iter('0', field->width - len, result);
	ft_putchar_iter('0', field->precision - len, result);
	safe_write(1, &array[i], len, result);
	if (field->flags & MINUS_ON)
		ft_putchar_iter(' ', field->width - len, result);
}
