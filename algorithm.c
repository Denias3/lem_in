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

t_room			*end_room_next(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

t_room			*search_room_type(t_room *rooms, short type)
{
	while (rooms != NULL)
	{
		if (rooms->type == type)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

int				ended_way(t_room *room)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->next_rooms[i]->visit == 0)
			j++;
		i++;
	}
	return (j);
}

int				possible_ways(t_room *room)
{
	int			j[2];

	j[0] = ended_way(room);
	room = end_room_next(room);
	j[1] = ended_way(room);
	if (j[0] > 0 && j[1] > 0)
	{
		return (j[0] < j[1] ? j[0] : j[1]);
	}
	else
		return (0);
}

t_room			*search_start_room(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 1)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

//void			realoc_xlink(t_room *room, int position)
//{
//	t_room		**tmp;
//	int			i;
//	int			j;
//
//	tmp = (t_room**)malloc(sizeof(t_room*) * (size_link(room)));
//	i = 0;
//	j = 0;
//	while (room->next_rooms[i] != NULL)
//	{
//		if (i != position)
//		{
//			tmp[j] = room->next_rooms[i];
//			j++;
//		}
//		i++;
//	}
//	tmp[j] = NULL;
//	free(room->next_rooms);
//	room->next_rooms = tmp;
//}

int				delet_xlink(t_room *room, int id)
{
	int			i;

	i = 0;
	if (room->visit > 1)
	{
		while (room->next_rooms[i] != NULL)
		{
			if (room->next_rooms[i]->id == id)
			{
				room->closed_links[i] = 4;
				room->visit = 0;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void			search_xlink(t_room *room, t_anthill *ant)
{
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if ((room->type == 0 || room->type == 3 || room->type == 4) && room->visit > 1)
		{
			if (delet_xlink(room->next_rooms[ant->ways[i][j + 1]], room->id) == 0)
			{
				room->closed_links[ant->ways[i][j + 1]] = 4;
				room->visit = 0;
				break ;
			}
		}
		j++;
	}
}

int				check_xlink(t_room *room, t_anthill *ant)
{
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	room = search_start_room(room);
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if ((room->type == 0 || room->type == 3 || room->type == 4) && room->visit > 1)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void			null_visit_close(t_room *rooms)
{
	int			i;
	int			size;

	while (rooms != NULL)
	{
		i = 0;
		rooms->visit = 0;
		size = size_link(rooms);
		while (size > i)
		{
			if (rooms->closed_links[i] != 4)
				rooms->closed_links[i] = 0;
			i++;
		}
		rooms = rooms->next;
	}
}

void			all_creat_closed_links(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->closed_links = creat_closed_links(size_link(rooms));
		rooms = rooms->next;
	}
}

int 			link_search(t_room *rooms, int id_room)
{
	int 		i;

	i = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		if (rooms->next_rooms[i]->id == id_room)
			return (i);
		i++;
	}
	return (-1);
}

void			revers_ways(t_room *rooms, t_anthill *ant)
{
	t_room		*room;
	int 		i;
	int 		j;

	i = 0;
	ant->r_ways = (int**)malloc(sizeof(int*) * len_int(ant->ways));
	ant->r_ways[len_int(ant->ways) - 1] = NULL;
	while (ant->ways[i] != NULL)
	{
		j = 0;
		room = rooms;
		while (j <= ant->ways[i][0])
		{
			if (j == 0)
			{
				ant->r_ways[i] = (int *) malloc(sizeof(int) * (ant->ways[i][j] + 1));
				ant->r_ways[i][j] = ant->ways[i][j];
			}
			else
			{
				ant->r_ways[i][j] = link_search(room->next_rooms[ant->ways[i][j]], room->id);
				room = room->next_rooms[ant->ways[i][j]];
			}
			j++;
		}
		ant->r_ways[i] = my_intrevers(ant->r_ways[i]);
		i++;
	}
}

void			revers_shortest_ways(t_room *rooms, t_anthill *ant)
{
	t_room		*room;
	int 		i;

	i = 0;
	room = rooms;
	while (i <= ant->shortest_way[0])
	{
		if (i == 0)
		{
			ant->r_shortest_way = (int*)malloc(sizeof(int) * (ant->shortest_way[i] + 1));
			ant->r_shortest_way[i] = ant->shortest_way[i];
		}
		else
		{
			ant->r_shortest_way[i] = link_search(room->next_rooms[ant->shortest_way[i]], room->id);
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
//	print_rooms(rooms, 2);

}

void			algorithm(t_anthill *ant, t_room *rooms)
{
	all_creat_closed_links(rooms);
	shortest_way(rooms, ant);
 	while ((possible_ways(rooms)) > 0 && to_position_2(rooms) == 0)
	{
//		print_rooms(rooms, 2);
		if (short_way(rooms, ant, 0) == 0)
		{

			if (check_xlink(rooms, ant) == 1)
			{
				print_rooms(rooms, 2);

				del_copies(rooms, ant);
				search_xlink(rooms, ant);
				free_ways(ant);
				null_visit_close(rooms);
			}
			else
				rooms_sharing(rooms, ant);
		}
		print_ways(rooms, ant, 0);
	}
//	print_rooms(rooms, 2);
	print_ways(rooms, ant, 0);
	del_copies(rooms, ant);

	null_visit_close(rooms);

	revers_ways(search_start_room(rooms), ant);
//	print_ways(rooms, ant, 1);
	go_ants(rooms, ant);
//	ft_printf("\n\n");
//	print_way(rooms, ant->r_ways[0], 0);
//	print_way(rooms, ant->r_ways[1], 1);
}
