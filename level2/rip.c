/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:33:57 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 21:04:54 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(char *s)
{
	size_t	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

void	ft_get_balance(char *s, int *open, int *closed)
{
	int	i;
	int	balance;

	*open = 0;
	*closed = 0;
	balance = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')')
		{
			if (balance > 0)
				balance--;
			else
				(*closed)++;	
		}
		i++;
	}
	*open = balance;
}

void	ft_balance(char *str, size_t len, size_t start, int open, int closed, int balance)
{
	if (start == len)
	{
		if (closed == 0 && open == 0 && balance == 0)
			puts(str);
		return ;
	}
	if (str[start] == '(' && open > 0)
	{
		str[start] = ' ';
		ft_balance(str, len, start + 1, open - 1, closed, balance);
		str[start] = '(';
	}
	else if (str[start] == ')' && closed > 0)
	{
		str[start] = ' ';
		ft_balance(str, len, start + 1, open, closed - 1, balance);
		str[start] = ')';
	}
	if (str[start] == '(')
		ft_balance(str, len, start + 1, open, closed, balance + 1);
	else if (str[start] == ')' && balance > 0)
		ft_balance(str, len, start + 1, open, closed, balance - 1);
	else
		ft_balance(str, len, start + 1, open, closed, balance);
}

int	main(int ac, char **av)
{
	size_t	len;
	int		open;
	int		closed;

	if (ac != 2 || av[1][0] == '\0')
		return (1);
	len = ft_strlen(av[1]);
	ft_get_balance(av[1], &open, &closed);
	ft_balance(av[1], len, 0, open, closed, 0);
	return (0);
}
