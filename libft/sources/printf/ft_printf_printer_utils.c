/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printer_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:51:17 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:50 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_num_to_str(int num, char *array)
{
	int	i;
	int	sign;

	ft_bzero(array, 11);
	i = 9;
	sign = 1;
	if (num < 0)
		sign = -1;
	while (num / 10 * sign > 0)
	{
		if (sign == 1)
			array[i] = num % 10 + '0';
		else if (sign == -1)
			array[i] = num % 10 * -1 + '0';
		num = num / 10;
		i--;
	}
	if (sign == 1)
		array[i] = num % 10 + '0';
	else if (sign == -1)
		array[i] = num % 10 * -1 + '0';
	return (i);
}

int	ft_unum_to_str(unsigned int num, char *array)
{
	int	i;

	ft_bzero(array, 11);
	i = 9;
	while (num / 10 > 0)
	{
		array[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	array[i] = num % 10 + '0';
	return (i);
}

int	ft_num_to_hex(size_t num, char *array, int is_addr, int is_upper)
{
	int	i;

	ft_bzero(array, 19);
	i = 18;
	if (num == 0)
	{
		i--;
		array[i] = '0';
	}
	while (num > 0)
	{
		i--;
		if (num % 16 > 9)
			array[i] = num % 16 + 87 - is_upper;
		else
			array[i] = num % 16 + 48;
		num = num / 16;
	}
	if (is_addr == 1)
	{
		array[i - 1] = 'x';
		array[i - 2] = '0';
		i -= 2;
	}
	return (i);
}
