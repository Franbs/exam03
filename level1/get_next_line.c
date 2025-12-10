/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 14:36:13 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1

size_t	ft_strlen(char *s)
{
	size_t	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l])
		l++;
	return (l);
}

char	*ft_concat_free(char *s1, char *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc(len1 + len2 + 1);
	if (!s3)
		return (free(s1), NULL);
	i = 0;
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		s3[i + len1] = s2[i];
		i++;
	}
	s3[len1 + len2] = '\0';
	return (free(s1), s3);
}

char	*ft_get_next_line(int fd)
{
	char	*line;
	size_t	bytes_read;
	char	buffer[BUFFER_SIZE];
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	bytes_read = 1;
	line = NULL;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		buffer[bytes_read] = '\0';
		stash[fd] = ft_concat_free(stash[fd], buffer);
		if (strchr(buffer, '\n'))
			break ;
	}
	if (!stash[fd] || !*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, line);
	line = stash[fd];
	return (stash[fd] = NULL, line);
}

char	*ft_concat_char(char *s, char c)
{
	char	*new_s;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	new_s = (char *)malloc(len + 2);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = c;
	new_s[i + 1] = '\0';
	return (free(s), new_s);
}

char	*get_next_line_v2(int fd)
{
	char	*line;
	size_t	bytes_read;
	char	c;

	line = NULL;
	while (1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read < 0)
			return (free(line), NULL);
		if (bytes_read == 0)
		{
			if (!line)
				return (NULL);
			return (line);
		}
		line = ft_concat_char(line, c);
		if (!line)
			return (NULL);
		if (c == '\n')
			break ;
	}
	return (line);
}

int	main(int ac, char **av)
{
	char	*line;
	int		fd;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	//while (1)
	//{
		line = get_next_line_v2(fd);
	//	if (!line)
	//		break ;
		printf("%s", line);
	//	free(line);
	//}
	return (0);
}
