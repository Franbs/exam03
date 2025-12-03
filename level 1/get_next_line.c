/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:55:56 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/03 02:56:40 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif
#define MAX_FD 1024

static size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*ft_concat_free(char *s1, const char *s2)
{
	char	*new_s;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	new_s = (char *)malloc(len1 + len2 + 1);
	if (!new_s)
	{
		free(s1);
		return (NULL);
	}
	
	size_t i = 0;
	while (i < len1)
	{
		new_s[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		new_s[len1 + i] = s2[i];
		i++;
	}
	new_s[len1 + len2] = '\0';
	free(s1);
	return (new_s);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE); 
		if (bytes_read == -1)
		{
			free(stash[fd]);
			stash[fd] = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			stash[fd] = ft_concat_free(stash[fd], buffer);
		if (!stash[fd])
			return (NULL);
	}
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	char *line = stash[fd];
	stash[fd] = NULL; 
	return (line);
}
