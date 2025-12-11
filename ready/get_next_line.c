/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/11 19:50:32 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1000

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

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
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

char	*ft_get_line_from_stash(char *str)
{
	char	*eol;
	size_t	len;
	char	*line;
	size_t	i;

	if (!str || !*str)
		return (NULL);
	eol = ft_strchr(str, '\n');
	if (eol)
		len = ft_strlen(str) - ft_strlen(eol) + 1;
	else
		len = ft_strlen(str);
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_update_stash(char *str)
{
	char	*eol;
	char	*rest;
	size_t	len;
	size_t	i;

	eol = ft_strchr(str, '\n');
	if (!eol)
		return (free(str), NULL);
	eol++;
	len = ft_strlen(eol);
	if (len == 0)
		return (free(str), NULL);
	rest = (char *)malloc(len * 1);
	if (!rest)
		return (free(str), NULL);
	i = 0;
	while (i < len)
	{
		rest[i] = eol[i];
		i++;
	}
	rest[len] = '\0';
	return (free(str), rest);
}

char	*ft_get_next_line(int fd)
{
	char	*line;
	size_t	bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash[fd] = ft_concat_free(stash[fd], buffer);
		if (!stash[fd])
			return (NULL);
	}
	if (!stash[fd] || !*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = ft_get_line_from_stash(stash[fd]);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = ft_update_stash(stash[fd]);
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
		line = ft_get_next_line(fd);
	//	if (!line)
	//		break ;
		printf("%s", line);
	//	free(line);
	//}
	return (0);
}
