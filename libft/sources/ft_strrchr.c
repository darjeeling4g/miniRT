/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:38:18 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:23:59 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*temp;
	unsigned char	value;

	value = (unsigned char)c;
	temp = NULL;
	while (*s)
	{
		if (*s == value)
			temp = (char *)s;
		s++;
	}
	if (*s == value)
		temp = (char *)s;
	return (temp);
}
