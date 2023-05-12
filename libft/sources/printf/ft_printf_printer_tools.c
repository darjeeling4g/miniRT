/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printer_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:04:10 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:25:42 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	safe_write(int fd, char *ptr, size_t len, int *result)
{
	ssize_t	byte;
	size_t	offjet;

	if (*result == -1)
		return ;
	offjet = 0;
	while (offjet < len)
	{
		byte = write(fd, ptr + offjet, len - offjet);
		if (byte < 0)
		{
			*result = -1;
			return ;
		}
		offjet += byte;
	}
	*result += len;
}

void	ft_putchar_iter(char c, int len, int *result)
{
	if (*result == -1)
		return ;
	if (len < 1)
		return ;
	while (len)
	{
		safe_write(1, &c, 1, result);
		if (*result == -1)
			return ;
		len--;
	}
}

void	ft_putsign(t_info *field, int num, int *result)
{
	char	flag;

	if (*result == -1)
		return ;
	flag = field->flags;
	if (num >= 0)
	{
		if (flag & PLUS_ON)
			safe_write(1, "+", 1, result);
		else if (flag & BLANK_ON)
			safe_write(1, " ", 1, result);
	}
	else
		safe_write (1, "-", 1, result);
}
