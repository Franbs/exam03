/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:20:50 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 18:34:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	ft_print_sol(int *queens, int board_size)
{
	int	i;

	i = 0;
	while (i < board_size)
	{
		printf("%i", queens[i]);
		if (i != board_size)
			printf(" ");
		i++;
	}
	printf("\n");
}

int	ft_is_safe(int *queens, int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (row == queens[i])
			return (1);
		if (row - queens[i] == col - i || row - queens[i] == -(col - i))
			return (1);
		i++;
	}
	return (0);
}

void	ft_solve(int *queens, int board_size, int col)
{
	int	row;

	if (col == board_size)
		ft_print_sol(queens, board_size);
	row = 0;
	while (row < board_size)
	{
		if (ft_is_safe(queens, row, col) == 0)
		{
			queens[col] = row;
			ft_solve(queens, board_size, col + 1);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	board_size;
	int	*queens;

	if (ac != 2)
		return (1);
	board_size = atoi(av[1]);
	if (board_size < 4)
		return (printf("\n"), 0);
	queens = malloc(sizeof(int) * board_size);
	if (!queens)
		return (1);
	ft_solve(queens, board_size, 0);
	return (0);
}
