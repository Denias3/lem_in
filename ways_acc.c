/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_acc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:34:47 by emeha             #+#    #+#             */
/*   Updated: 2019/10/07 18:34:52 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ways_acc(int *ways_acc, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d-", ways_acc[i]);
		i++;
	}
	ft_putchar('\n');
}

void	init_ways_acc(int *ways_acc, int size)
{
	while (--size >= 0)
		ways_acc[size] = 0;
}

void	cop_ways_acc(int *ways_acc, int *ways_acc_tmp,  int size)
{
	while (--size >= 0)
		ways_acc[size] = ways_acc_tmp[size];
}

int		iteration_ways_acc(int *ways_acc, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (ways_acc[i] == 1)
		{
			ways_acc[i] = 0;
		}
		else if (ways_acc[i] == 0)
		{
			ways_acc[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	null_state_rooms(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->state = 0;
		rooms->visit = 0;
		rooms = rooms->next;
	}
}

int 	shortest_way_allow(t_room *rooms, t_anthill *ant, int count)
{
	t_room	*st_room;
	t_room	*stop_room;
	int 	count_tmp;

	count_tmp = 0;
	st_room = search_room_type(rooms, 1);
	stop_room = search_room_type(rooms, 2);
	null_state_rooms(rooms);
	st_room->state = ant->ants;
	while (stop_room->state != ant->ants)
	{
		go_way(stop_room, ant->r_shortest_way, 0);
		count_tmp++;
	}
	null_state_rooms(rooms);
	if (count_tmp < count)
		return (1);
	return (0);
}

int		*ways_allow(t_room *rooms, t_anthill *ant)
{
	t_room	*st_room;
	t_room	*stop_room;
	int		*ways_acc;
	int		*ways_acc_tmp;
	int		j;
	int 	count;
	int 	count_tmp;

	count = -1;
	ways_acc = (int*)malloc(sizeof(int) * (len_int(ant->ways) - 1));
	ways_acc_tmp = (int*)malloc(sizeof(int) * (len_int(ant->ways) - 1));
	init_ways_acc(ways_acc_tmp, (len_int(ant->ways) - 1));
	st_room = search_room_type(rooms, 1);
	stop_room = search_room_type(rooms, 2);
	while (iteration_ways_acc(ways_acc_tmp, (len_int(ant->ways) - 1)))
	{
		count_tmp = 0;
		null_state_rooms(rooms);
		st_room->state = ant->ants;
		while (stop_room->state != ant->ants)
		{
			j = 0;
			while (ant->r_ways[j] != NULL)
			{
				if (ways_acc_tmp[j] == 1)
					go_way(stop_room, ant->r_ways[j], 0);
				j++;
			}
			count_tmp++;
		}
		if ((count_tmp < count) || count == -1)
		{
			count = count_tmp;
			cop_ways_acc(ways_acc, ways_acc_tmp, (len_int(ant->ways) - 1));
		}
	}
	free(ways_acc_tmp);
	null_state_rooms(rooms);
	if (shortest_way_allow(rooms, ant, count) == 1)
		return (NULL);
	return (ways_acc);
}
