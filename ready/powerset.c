/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/14 23:00:17 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int	ft_zero_present(char **numbers, int len)
{
	int	i;

	i = 2;
	while (numbers[i])
	{
		if (atoi(numbers[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_sol(int *sol, int sol_idx, int zero_present)
{
	int i;

	i = 0;
	while (i < sol_idx)
	{
		printf("%i", sol[i]);
		if (i < sol_idx - 1)
			printf(" ");
		i++;
	}
	if (zero_present == 1)
	{
		printf("\n");
		i = 0;
		while (i < sol_idx)
		{
			printf("%i ", sol[i]);
			i++;
		}
		printf("0");
	}
	printf("\n");
}

void	ft_powerset(int *numbers, int obj, int len, int *nums, int sum, int start, int sol_index, int *sol_found, int zero_present)
{
	int	i;

	if (sum == obj)
	{
		(*sol_found) = 1;
		ft_print_sol(nums, sol_index, zero_present);
	}
	i = start;
	while (i < len)
	{
		nums[sol_index] = numbers[i];
		ft_powerset(numbers, obj, len, nums, sum + numbers[i], i + 1, sol_index + 1, sol_found, zero_present);
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
	int	zero_present;

	if (ac < 3)
		return (1);
	obj = atoi(av[1]);
	i = 2;
	zero_present = ft_zero_present(av, len);
	if (zero_present == 1)
		len = ac - 3;
	else
		len = ac - 2;
	j = 0;
	numbers = (int *)malloc(sizeof(int) * len);
	if (!numbers)
		return (1);
	while (i < ac)
	{
		if (atoi(av[i]) != 0)
		{
			numbers[j] = atoi(av[i]);
			j++;
		}
		i++;
	}
	nums = (int *)malloc(sizeof(int) * len);
	if (!nums)
		return (free(numbers), 1);
	sol_found = 0;
	ft_powerset(numbers, obj, len, nums, 0, 0, 0, &sol_found, zero_present);
	if (sol_found == 0)
		printf("\n");
	return (free(numbers), free(nums), 0);
}
