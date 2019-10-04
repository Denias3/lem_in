/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 04:35:24 by fschille          #+#    #+#             */
/*   Updated: 2019/09/12 04:35:26 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room		*end_room_next(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

t_room          *search_room_type(t_room *rooms, short type)
{
    while (rooms != NULL)
    {
        if (rooms->type == type)
			return (rooms);
		rooms = rooms->next;
    }
    return (NULL);
}

void			print_bfs(t_room *rooms)
{
	while (rooms != NULL)
	{
		ft_printf("%s-", rooms->name);
		rooms = rooms->bfs_next;
	}
}

int 			ch_bf(t_room *room)
{
	int i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->next_rooms[i]->bf == -1)
			return (0);
		i++;
	}
	return (1);
}

void			free_bf(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 1)
			rooms->bf = 0;
		else
			rooms->bf = -1;
		rooms = rooms->next;
	}
}

t_room          *search_room_bf(t_room *rooms, int bf)
{
	int i;

	i = 0;
	while (rooms != NULL)
	{
		if (rooms->bf == bf && ch_bf(rooms) == 0)
		{
			while (rooms->next_rooms[i] != NULL)
			{
				if (rooms->next_rooms[i]->bf == -1)
				{
					if (rooms->closed_links != 0 && rooms->closed_links[i] != 1)
						return (rooms->next_rooms[i]);
					else if (rooms->closed_links == 0)
						return (rooms->next_rooms[i]);
				}
				i++;
			}
		}
		rooms = rooms->next;
	}
	return (NULL);
}

int				end_bf(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->bf == -1)
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

void			go_bf(t_room *rooms)
{
	t_room	*tmp;
	t_room	*tmp2;
	int		bf;

	tmp2 = search_room_type(rooms, 1);
	bf = 1;
	while (end_bf(rooms) == 0)
	{
		tmp = search_room_bf(rooms, bf - 1);
		if (tmp == NULL)
			bf++;
		else
		{
			tmp->bf = bf;
			tmp->bfs_prev = tmp2;
			tmp2->bfs_next = tmp;
			tmp2 = tmp;
		}
	}
}


void            to_position(t_room *rooms)
{
	free_bf(rooms);
	go_bf(rooms);
}

int             ended_way(t_room *start)
{
	int         i;

	i = 0;
	while (start->next_rooms[i] != NULL)
	{
		if (start->next_rooms[i]->visit == 0)
			return (0);
		i++;
	}
	return (1);
}

void            realoc_xlink(t_room *room, int position)
{
	t_room      **tmp;
	int         i;
	int         j;

	tmp = (t_room**)malloc(sizeof(t_room*) * (size_link(room) - 1));
	i = 0;
	j = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (i != position)
		{
			tmp[j] = room->next_rooms[i];
			j++;
		}
		i++;
	}
	free(room->next_rooms);
	room->next_rooms = tmp;
}

int             delet_xlink(t_room *room, int id)
{
	int         i;

	i = 0;
	if (room->visit > 1)
	{
		while (room->next_rooms[i] != NULL)
		{
			if (room->next_rooms[i]->id == id)
			{
				realoc_xlink(room, i);
				room->visit = 0;
				return (0);
			}
		}
	}
	return (1);
}

int             search_xlink(t_room *room, t_anthill *ant, int type)
{
	int         i;
	int         j;
	int         size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if (room->type == 0 && room->visit > 1)
		{
			if (type == 0 && delet_xlink(room->next_rooms[ant->ways[i][j + 1]], room->id) == 0)
			{
				realoc_xlink(room, ant->ways[i][j + 1]);
				room->visit = 0;
			}
			return (1);
		}
		j++;
	}
	return (0);
}

void			algorithm(t_anthill *ant, t_room *rooms)
{
	to_position(rooms);
	short_way(rooms, ant);
	rooms_sharing(rooms, ant);
	join_rooms_main(rooms, ant);
	print_rooms(rooms, 0);
//	search_xlink(rooms, ant);
//    print_vay(rooms, ant);
//    print_bfs(rooms);
//    print_rooms(rooms);
//    go_ants(rooms, ant);
}
//void			algorithm(t_anthill *ant, t_room *rooms) {
//	while (ended_way(rooms) == 0 && ended_way(end_room_next(rooms)) == 0) {
//		to_position(rooms);
//		if (short_way(rooms, ant) == 0) {
//			rooms_sharing(rooms, ant);
//			if (search_xlink(rooms, ant, 1) == 1) {
//				join_rooms_main(rooms);
//				search_xlink(rooms, ant, 0);
//				free_track_record(ant);
//			}
//		}
//		print_rooms(rooms, 0);
//	}
//	print_rooms(rooms, 0);
//}
