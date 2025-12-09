/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:53:01 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/03 11:28:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_BUFFER_SIZE 1024

int	main(int ac, char **av)
{
	char	buffer[MAX_BUFFER_SIZE];
	size_t	bytes_read;
	char	*content;
	char	*tmp;
	int		l;
	int		i;

	if (ac != 2)
		return (1);
	content = NULL;
	l = 0;
	bytes_read = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE);
	while (bytes_read > 0)
	{
		tmp = (char *)realloc(content, l + bytes_read + 1);
		if (!tmp)
			return (free(content), 1);
		content = tmp;
		i = 0;
		while (i < bytes_read)
		{
			content[l + i] = buffer[i];
			i++;
		}
		content[l + bytes_read] = '\0';
		l += bytes_read;
		bytes_read = read(STDIN_FILENO, buffer, MAX_BUFFER_SIZE);
	}
	printf("%s", content);
	if (content)
		free(content);
	if (bytes_read == -1)
		return (perror("error"), 1);
	return (0);
}
