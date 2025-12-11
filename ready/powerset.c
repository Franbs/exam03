/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/11 21:32:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void	ft_print_sol(int *sol, int sol_len)
{
	int	i;

	i = 0;
	while (i < sol_len)
	{
		printf("%i", sol[i]);
		if (i < sol_len - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_powerset(int *numbers, int obj, int len, int *nums, int sum, int start, int sol_index, int *sol_found)
{
	int	i;

	if (sum == obj)
	{
		(*sol_found) = 1;
		ft_print_sol(nums, sol_index);
	}
	i = start;
	while (i < len)
	{
		nums[sol_index] = numbers[i];
		ft_powerset(numbers, obj, len, nums, sum + numbers[i], i + 1, sol_index + 1, sol_found);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	obj;
	int	*numbers;
	int	i;
	int	j;
	int	len;
	int	*nums;
	int	sol_found;

	if (ac < 3)
		return (1);
	obj = atoi(av[1]);
	i = 2;
	len = ac - 2;
	j = 0;
	numbers = (int *)malloc(sizeof(int) * len);
	if (!numbers)
		return (1);
	while (i < ac)
	{
		numbers[j] = atoi(av[i]);
		i++;
		j++;
	}
	nums = (int *)malloc(sizeof(int) * len);
	if (!nums)
		return (free(numbers), 1);
	sol_found = 0;
	ft_powerset(numbers, obj, len, nums, 0, 0, 0, &sol_found);
	if (sol_found == 0)
		printf("\n");
	return (free(numbers), free(nums), 0);
}
