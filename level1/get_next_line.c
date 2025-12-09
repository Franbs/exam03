/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_blind.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:26:26 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/09 18:18:59 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 1

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_concat(char *s1, char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(s1_len + s2_len + 1);
	if (!new_str)
		return (free(s1), NULL);
	i = 0;
	while (i < s1_len)
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		new_str[i + s1_len] = s2[i];
		i++;
	}
	new_str[s1_len + s2_len] = '\0';
	return (free(s1), new_str);
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[1024];
	char		buffer[BUFFER_SIZE + 1];
	size_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			stash[fd] = ft_concat(stash[fd], buffer);
		if (!stash[fd])
			return (NULL);
		if (strchr(buffer, '\n'))
			break ;
	}
	if (!stash[fd] || !*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = stash[fd];
	stash[fd] = NULL;
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("filter.c", O_RDONLY);
	if (fd == -1)
		return (printf("fd"), 1);
	line = ft_get_next_line(fd);
	if (line)
		return (printf("%s", line), free(line), 0);
	return (0);
}
