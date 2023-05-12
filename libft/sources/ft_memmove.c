/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 22:04:16 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:21:58 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*temp_dst;
	const unsigned char	*temp_src;
	size_t				i;

	temp_dst = dst;
	temp_src = src;
	if (temp_dst == temp_src || len == 0)
		return (dst);
	else if (temp_dst > temp_src && temp_dst - temp_src < (long)len)
	{
		i = len;
		while (i > 0)
		{
			temp_dst[i - 1] = temp_src[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
