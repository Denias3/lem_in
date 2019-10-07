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

int 		check_ant_flow(t_room *st_rooms, int *way)
{
	int		i;
	int 	j;

	i = 1;
	j = 0;
	while (st_rooms->type != 2)
	{
		if (st_rooms->state == 0)
			j++;
		else
		{
			st_rooms = st_rooms->next_rooms[way[i]];
			break ;
		}
		st_rooms = st_rooms->next_rooms[way[i]];
		i++;
	}
	while (st_rooms->type != 2)
	{
		i++;
		if (st_rooms->state > 0)
			j++;
		st_rooms = st_rooms->next_rooms[way[i]];
	}
	return (j + 1);
}

void        go_way(t_room *st_rooms, int *way)
{
    int		i;
	int 	j;

    i = 1;
    j = check_ant_flow(st_rooms, way);
//	while (st_rooms->state == 0)
//	{
//		st_rooms = st_rooms->next_rooms[way[i]];
//		i++;
//	}
    while (j > 0)
    {
    	if (st_rooms->state > 0)
    	{
			st_rooms->next_rooms[way[i]]->visit = st_rooms->visit;
			st_rooms->next_rooms[way[i]]->state++;
			st_rooms->state--;
			ft_printf("L%d-%s ", st_rooms->next_rooms[way[i]]->visit, st_rooms->next_rooms[way[i]]->name);
		}
		st_rooms = st_rooms->next_rooms[way[i]];
        i++;
        j--;
    }
}

void    go_ants(t_room *rooms, t_anthill *ant)
{
    t_room *st_room;
    t_room *stop_room;
	int j;

	st_room = search_room_type(rooms, 1);
	stop_room = search_room_type(rooms, 2);
	st_room->state = ant->ants;
	print_ways(rooms, ant, 0);
    while (stop_room->state != ant->ants)
    {
		j = 0;
		(st_room->visit)++;
		while (ant->ways[j] != NULL)
		{

			go_way(st_room, ant->ways[j]);
//			ft_printf(" ");

			j++;
		}
//		print_ways(rooms, ant, 0);
		ft_printf("\n");
	}

}