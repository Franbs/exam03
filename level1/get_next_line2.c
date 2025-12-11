/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/11 18:59:50 by fbanzo-s         ###   ########.fr       */
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
