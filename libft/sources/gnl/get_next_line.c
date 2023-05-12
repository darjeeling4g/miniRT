/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siyang <siyang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:08:43 by siyang            #+#    #+#             */
/*   Updated: 2023/02/25 21:17:31 by siyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_next_line(int fd, char *buffer, char **backup, char **result);
static void	get_until_eol(char *buffer, char **backup, char **result);
static char	*free_n_return(char **ptr1, char **ptr2);

char	*get_next_line(int fd)
{
	static char	*backup[257];
	char		*buffer;
	char		*result;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	result = ft_strdup("");
	if (result == NULL)
		return (free_n_return(NULL, &result));
	if (backup[fd])
	{
		buffer = backup[fd];
		get_until_eol(buffer, &backup[fd], &result);
		free(buffer);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (free_n_return(&buffer, &result));
	buffer[BUFFER_SIZE] = '\0';
	return (read_next_line(fd, buffer, &backup[fd], &result));
}

static char	*read_next_line(int fd, char *buffer, char **backup, char **result)
{
	ssize_t	nbyte;

	while (!*backup)
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte < 0 || (nbyte == 0 && **result == '\0'))
			return (free_n_return(&buffer, result));
		else if (nbyte == 0)
			break ;
		else
		{
			buffer[nbyte] = '\0';
			get_until_eol(buffer, backup, result);
		}
	}
	free(buffer);
	return (*result);
}

static void	get_until_eol(char *buffer, char **backup, char **result)
{
	char	*temp;

	temp = ft_strchr(buffer, '\n');
	if (temp != NULL)
	{
		*backup = ft_strdup(temp + 1);
		temp[1] = '\0';
	}
	else
		*backup = NULL;
	temp = *result;
	*result = ft_strjoin(*result, buffer);
	free(temp);
}

static char	*free_n_return(char **ptr1, char **ptr2)
{
	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (NULL);
}
