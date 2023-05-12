/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yangsiseon <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:31:41 by yangsiseon        #+#    #+#             */
/*   Updated: 2023/02/25 21:24:06 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1)
	{
		if (ft_strchr(set, *s1) == NULL)
			break ;
		s1++;
	}
	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_strchr(set, s1[len - 1]) == NULL)
			break ;
		len--;
	}
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}
