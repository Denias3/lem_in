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

int			long_path_size(t_anthill *ant, int *ways_acc)
{
	int		i;
	int		size;

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

int			my_ceil(int num1, int num2)
{
	int		res;

	if (num1 % num2 == 0)
		res = num1 / num2;
	else
		res = (num1 / num2) + 1;
	return (res);
}

int			search_count(int ants, int size_big_way)
{
	return ((ants - 1) + size_big_way);
}

int			open_ways(int *ways_acc, int size)
{
	int		i;
	int		res;

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

int			*right_ways(t_anthill *ant, int count, int tmp_count)
{
	int		size_ways;
	int		*ways_acc;
	int		*res_ways_acc;
	int		ants;

	size_ways = len_int(ant->ways) - 1;
	ways_acc = new_ways_acc(size_ways);
	res_ways_acc = new_ways_acc(size_ways);
	count = search_count(ant->ants, ant->shortest_way[0]);
	while (iteration_ways_acc(ways_acc, size_ways) == 1)
	{
		ants = my_ceil(ant->ants, open_ways(ways_acc, size_ways));
		tmp_count = search_count(ants, long_path_size(ant, ways_acc));
		if (tmp_count <= count)
		{
			cop_ways_acc(res_ways_acc, ways_acc, size_ways);
			count = tmp_count;
		}
	}
	free(ways_acc);
	return (search_count(ant->ants, ant->shortest_way[0])
	== count ? NULL : res_ways_acc);
}
