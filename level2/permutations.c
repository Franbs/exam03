/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:56:56 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 18:34:49 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_swap(char *c1, char *c2)
{
	char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

char	*ft_sort(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (str[j] > str[j + 1])
				ft_swap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
	return (str);
}

void	ft_permute(char *str, size_t start)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (start == len)
		puts(str);
	i = start;
	while (i < len)
	{
		ft_swap(&str[start], &str[i]);
		ft_permute(str, start + 1);
		ft_swap(&str[start], &str[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	char	*str;

	if (ac != 2 || av[1][0] == '\0')
		return (printf("args not valid"), 1);
	str = (char *)malloc(ft_strlen(av[1]) + 1);
	if (!str)
		return (perror("error "), 1);
	str = ft_sort(av[1]);
	ft_permute(str, 0);
	return (0);
}
