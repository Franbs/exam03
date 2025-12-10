/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:23:37 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/10 18:34:43 by fbanzo-s         ###   ########.fr       */
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

void	ft_powerset(int *numbers, int obj, int len, int *nums, int sum, int start, int sol_len)
{
	int	i;

	if (sum == obj)
	{
		ft_print_sol(nums, sol_len);
		return ;
	}
	if (sum > obj)
		return ;
	i = start;
	while (i < len)
	{
		nums[sol_len] = numbers[i];
		ft_powerset(numbers, obj, len, nums, sum + numbers[i], i + 1, sol_len + 1);
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

	if (ac < 3)
		return (1);
	obj = atoi(av[1]);
	i = 2;
	len = ac - 2;
	j = 0;
	numbers = malloc(sizeof(int) * len);
	if (!numbers)
		return (1);
	while (i < ac)
	{
		numbers[j] = atoi(av[i]);
		i++;
		j++;
	}
	nums = malloc(sizeof(int) * len);
	if (!nums)
		return (free(numbers), 1);
	ft_powerset(numbers, obj, len, nums, 0, 0, 0);
	return (free(numbers), free(nums), 0);
}
