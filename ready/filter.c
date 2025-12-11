/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:39:46 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/11 19:59:51 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE	1024

char	*ft_replace(char *str, char *filter, int start, int end)
{
	while (start < end)
	{
		str[start] = '*';
		start++;
	}
	return (str);
}

char	*ft_filter(char *str, char *filter)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == filter[0])
		{
			k = i;
			j = 0;
			while (str[k] && str[k] == filter[j])
			{
				k++;
				j++;
			}
			if (j == strlen(filter))
			{
				ft_replace(str, filter, i, k);
				i = k - 1;
			}
		}
		i++;
	}
	return (str);
}

char	*ft_read_content(void)
{
	int		total_l;
	int		i;
	char	*content;
	char	*tmp;
	char	buffer[BUFFER_SIZE];
	size_t	bytes_read;

	total_l = 0;
	content = NULL;
	bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		tmp = (char *)realloc(content, total_l + bytes_read + 1);
		if (!tmp)
			return (free(content), NULL);
		content = tmp;
		i = 0;
		while (i < bytes_read)
		{
			content[i + total_l] = buffer[i];
			i++;
		}
		content[bytes_read + total_l] = '\0';
		total_l += bytes_read;
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (perror("error"), free(content), NULL);
	return (content);
}

int	main(int ac, char **av)
{
	char	*content;

	if (ac != 2 || av[1][0] == '\0')
		return (printf("args not valid"), 1);
	content = ft_read_content();
	content = ft_filter(content, av[1]);
	printf("%s", content);
	return (free(content), 0);
}
