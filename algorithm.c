/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <fschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 04:35:24 by fschille          #+#    #+#             */
/*   Updated: 2019/10/06 18:03:37 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				link_search(t_room *rooms, int id_room)
{
	int			i;

	i = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		if (rooms->next_rooms[i]->id == id_room)
			return (i);
		i++;
	}
	return (-1);
}

void			revers_ways(t_room *rooms, t_anthill *ant, int i, int j)
{
	t_room		*room;

	ant->r_ways = (int**)malloc(sizeof(int*) * len_int(ant->ways));
	ant->r_ways[len_int(ant->ways) - 1] = NULL;
	while (ant->ways[++i] != NULL)
	{
		j = -1;
		room = rooms;
		while (++j <= ant->ways[i][0])
		{
			if (j == 0)
			{
				ant->r_ways[i] = (int*)malloc(sizeof(int) *
						(ant->ways[i][j] + 1));
				ant->r_ways[i][j] = ant->ways[i][j];
			}
			else
			{
				ant->r_ways[i][j] = link_search(room->next_rooms
						[ant->ways[i][j]], room->id);
				room = room->next_rooms[ant->ways[i][j]];
			}
		}
		ant->r_ways[i] = my_intrevers(ant->r_ways[i]);
	}
}

void			revers_shortest_ways(t_room *rooms, t_anthill *ant)
{
	t_room		*room;
	int			i;

	i = 0;
	room = rooms;
	while (i <= ant->shortest_way[0])
	{
		if (i == 0)
		{
			ant->r_shortest_way = (int*)malloc(sizeof(int) *
					(ant->shortest_way[i] + 1));
			ant->r_shortest_way[i] = ant->shortest_way[i];
		}
		else
		{
			ant->r_shortest_way[i] = link_search(room->next_rooms
					[ant->shortest_way[i]], room->id);
			room = room->next_rooms[ant->shortest_way[i]];
		}
		i++;
	}
	ant->r_shortest_way = my_intrevers(ant->r_shortest_way);
}

void			shortest_way(t_room *rooms, t_anthill *ant)
{
	if (to_position_2(rooms) == 0 && (possible_ways(rooms)) > 0)
	{
		if (short_way(rooms, ant, 1) == 0)
		{
			revers_shortest_ways(search_start_room(rooms), ant);
			null_visit_close(rooms);
		}
	}
	else
		error("did not find a way");
}

void			algorithm(t_anthill *ant, t_room *rooms)
{
	all_creat_closed_links(rooms);
	shortest_way(rooms, ant);
	while ((possible_ways(rooms)) > 0 && to_position_2(rooms) == 0)
	{
		if (short_way(rooms, ant, 0) == 0)
		{
			if (check_xlink(rooms, ant) == 1)
			{
				del_copies(rooms, ant, 0, 0);
				search_xlink(rooms, ant);
				free_ways(ant);
				null_visit_close(rooms);
			}
			else
				rooms_sharing(rooms, ant);
		}
		else
			break ;
	}
	ft_printf("%s\n", ant->map);
	free(ant->map);
	del_copies(rooms, ant, 0, 0);
	null_visit_close(rooms);
	revers_ways(search_start_room(rooms), ant, -1, -1);
	go_ants(rooms, ant, right_ways(ant, 0, 0),
			-1);
}
