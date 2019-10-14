/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_ways.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:00:04 by fschille          #+#    #+#             */
/*   Updated: 2019/10/08 18:00:06 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*new_ways_acc(int size)
{
	int		*ways_acc;
	int 	i;

	ways_acc = (int*)malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		ways_acc[i] = 0;
		i++;
	}
	return (ways_acc);
}

int 		long_path_size(t_anthill *ant, int *ways_acc)
{
	int 	i;
	int 	size;

	i = 0;
	size = -1;
	while (ant->ways[i])
	{
		if (ways_acc[i] == 1 && ant->ways[i][0] > size)
			size = ant->ways[i][0];
		i++;
	}
	return (size);
}

int 		my_ceil(int num1, int num2)
{
	int 	res;

	if (num1 % num2 == 0)
		res = num1 / num2;
	else
		res = (num1 / num2) + 1;
	return (res);
}

int 		search_count(int ants, int size_big_way)
{
//	if (ants - 1 == 0)
//		ants -= 0;
//	else
//		ants -= 1;
	return ((ants - 1) + size_big_way);
}

int 		open_ways(int *ways_acc, int size)
{
	int 	i;
	int 	res;

	i = 0;
	res = 0;
	while (i < size)
	{
		if (ways_acc[i] == 1)
			res++;
		i++;
	}
	return (res);
}

int 		*right_ways(t_anthill *ant)
{
	int		size_ways;
	int		*ways_acc;
	int 	*res_ways_acc;
	int 	ants;
	int 	count;
	int 	tmp_count;
//	int 	i;

	size_ways = len_int(ant->ways) - 1;
	ways_acc = new_ways_acc(size_ways);
	res_ways_acc = new_ways_acc(size_ways);
	count = search_count(ant->ants, ant->shortest_way[0]);
	while (iteration_ways_acc(ways_acc, size_ways) == 1)
	{
		ants = my_ceil(ant->ants, open_ways(ways_acc, size_ways));
		tmp_count = search_count(ants, long_path_size(ant, ways_acc));
//		i = 0;
//		while (size_ways > i + 1)
//		{
//			ft_printf("%d(%d)-", ways_acc[i], i);
//			i++;
//		}
//		ft_printf("%d(%d)\n", ways_acc[i], i);
		if (tmp_count <= count)
		{
			cop_ways_acc(res_ways_acc, ways_acc, size_ways);
			count = tmp_count;
		}
	}
	free(ways_acc);
	return (res_ways_acc);
}
