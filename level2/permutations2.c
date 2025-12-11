/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:56:56 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/11 14:39:58 by fbanzo-s         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_swap(char *c1, char *c2)
{
	char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

int	ft_factorial(size_t len)
{
	if (len == 0 || len == 1)
		return (1);
	return (len * ft_factorial(len - 1));
}

void	ft_free_perms(char **perms, int factorial)
{
	int	i;

	i = 0;
	while (i < factorial)
	{
		if (perms[i])
			free(perms[i]);
		i++;
	}
	free(perms);
}

void	ft_print_perms(char **perms, int factorial)
{
	int	i;

	i = 0;
	while (i < factorial)
	{
		puts(perms[i]);
		i++;
	}
}

void	ft_sort_perms(char **perms, int factorial)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < factorial - 1)
	{
		j = 0;
		while (j < factorial - 1 - i)
		{
			if (ft_strcmp(perms[j], perms[j + 1]) > 0)
			{
				tmp = perms[j];
				perms[j] = perms[j + 1];
				perms[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_permute(char **perms, char *str, size_t len, size_t start, int *count)
{
	size_t	i;

	if (start == len)
	{
		ft_strcpy(perms[*count], str);
		(*count)++;
		return ;
	}
	i = start;
	while (i < len)
	{
		ft_swap(&str[start], &str[i]);
		ft_permute(perms, str, len, start + 1, count);
		ft_swap(&str[start], &str[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	size_t	len;
	int		factorial;
	char	**perms;
	char	*str;
	int		i;
	int		count;

	if (ac != 2 || av[1][0] == '\0')
		return (printf("args not valid"), 1);
	len = ft_strlen(av[1]);
	factorial = ft_factorial(len);
	perms = (char **)malloc(sizeof(char *) * (factorial + 1));
	if (!perms)
		return (1);
	perms[factorial] = NULL;
	i = 0;
	while (i < factorial)
	{
		perms[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!perms[i])
			return (ft_free_perms(perms, factorial), 1);
		i++;
	}
	str = (char *)malloc(ft_strlen(av[1]) + 1);
	if (!str)
		return (ft_free_perms(perms, factorial), 1);
	count = 0;
	ft_strcpy(str, av[1]);
	ft_permute(perms, str, len, 0, &count);
	ft_sort_perms(perms, factorial);
	ft_print_perms(perms, factorial);
	return (0);
}
