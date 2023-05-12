/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:03:25 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:22:26 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_num(int n);

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		i;
	int		pow;
	char	temp;

	len = len_num(n);
	if (n < 0)
		write(fd, "-", 1);
	while (len)
	{
		i = 1;
		pow = 1;
		while (i < len)
		{
			pow *= 10;
			i++;
		}
		if (n < 0)
			temp = (n / pow) * -1 + '0';
		else
			temp = n / pow + '0';
		write(fd, &temp, 1);
		n = n % pow;
		len--;
	}
}

static int	len_num(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
