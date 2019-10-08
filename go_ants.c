/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 11:37:18 by emeha             #+#    #+#             */
/*   Updated: 2019/10/02 11:37:21 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void        go_way(t_room *end_rooms, int *way, int v)
{
	int		i;

	i = 1;
	while (way[0] >= i)
	{
		if (end_rooms->next_rooms[way[i]]->state > 0)
		{
			end_rooms->visit = end_rooms->next_rooms[way[i]]->visit;
			end_rooms->next_rooms[way[i]]->state--;
			end_rooms->state++;
			if (v)
				ft_printf("L%d-%s ", end_rooms->visit, end_rooms->name);
		}

		end_rooms = end_rooms->next_rooms[way[i]];
		i++;
	}
}



void    go_ants(t_room *rooms, t_anthill *ant)
{
    t_room	*st_room;
    t_room	*stop_room;
	int		*ways_acc;

	int		j;
	ways_acc = ways_allow(rooms, ant);
	st_room = search_room_type(rooms, 1);
	stop_room = search_room_type(rooms, 2);
	st_room->state = ant->ants;
	while (stop_room->state != ant->ants)
    {
		j = 0;
		(st_room->visit)++;
		if (ways_acc == NULL)
		{
			go_way(stop_room, ant->r_shortest_way, 1);
		}
		else
		{
			while (ant->r_ways[j] != NULL)
			{
				if (ways_acc[j] == 1)
					go_way(stop_room, ant->r_ways[j], 1);
				j++;
			}
		}

		if (stop_room->state != ant->ants)
			ft_printf("\n");
	}
}