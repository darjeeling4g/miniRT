/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:14:14 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:22:05 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	unsigned char	value;
	size_t			i;

	temp = b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		temp[i] = value;
		i++;
	}
	return (b);
}
