/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:01:57 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:23:31 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = 0;
	while (*src)
	{
		if (srclen + 1 < dstsize)
		{
			*dst = *src;
			dst++;
		}
		src++;
		srclen++;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (srclen);
}
