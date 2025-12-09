/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:43:49 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/03 19:29:59 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static void ft_print_sol(int *board, int board_size)
{
	int col;

	col = 0;
	while (col < board_size)
	{
		printf("%i", board[col]);
		if (col < board_size - 1)
			printf(" ");
		col++;
	}
	printf("\n");
}

int	ft_is_safe(int *board, int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row)
			return (1);
		if (row - board[i] == col - i || row - board[i] == -(col - i))
			return (1);
		i++;
	}
	return (0);
}

void	ft_solve(int *board, int board_size, int col)
{
	int	row;

	if (col == board_size)
		ft_print_sol(board, board_size);
	row = 0;
	while (row < board_size)
	{
		if (ft_is_safe(board, row, col) == 0)
		{
			board[col] = row;
			ft_solve(board, board_size, col + 1);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	board_size;
	int	*board;

	if (ac != 2)
		return (1);
	board_size = atoi(av[1]);
	if (board_size < 4)
		return (printf("\n"), 0);
	board = malloc(sizeof(int) * board_size);
	if (!board)
		return (1);
	ft_solve(board, board_size, 0);
	return (0);
}
