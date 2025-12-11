/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:05:17 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 13:32:31 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_filter(char *filter)
{
	size_t	bytes_read;
	char	buffer[1024];
	size_t	i;
	size_t	j;

	bytes_read = read(STDIN_FILENO, buffer, 1024);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		i = 0;
		while (i < bytes_read)
		{
			if (!ft_strncmp(&buffer[i], filter, strlen(filter)))
			{
				j = 0;
				while (j < strlen(filter))
				{
					printf("*");
					j++;
					i++;
				}
			}
			else
			{
				printf("%c", buffer[i]);
				i++;
			}
		}	
		bytes_read = read(STDIN_FILENO, buffer, 1024);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	ft_filter(av[1]);
	return (0);
}
