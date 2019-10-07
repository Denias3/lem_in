/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 01:18:18 by fschille          #+#    #+#             */
/*   Updated: 2019/09/30 01:18:23 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*my_intrevers(int *way)
{
	int		i;
	int		tmp;
	int		m_i;

	i = 1;
	m_i = way[0];
	while (i < m_i)
	{
		tmp = way[i];
		way[i] = way[m_i];
		way[m_i] = tmp;
		i++;
		m_i--;
	}
	return (way);
}

t_room		*end_room(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

int			size_link(t_room *room)
{
	int		size;

	size = 0;
	while (room->next_rooms[size] != NULL)
		size++;
	return (size);
}

int			*creat_closed_links(int size)
{
	int		*closed_links;
	int		i;

	i = 0;
	closed_links = (int*)malloc(sizeof(int) * size);
	while (i < size)
	{
		closed_links[i] = 0;
		i++;
	}
	return (closed_links);
}

void		close_link(t_room *end_room, t_room *room)
{
	int		i;

	i = 0;
	while (end_room->next_rooms[i] != NULL)
	{
		if (end_room->next_rooms[i] == room)
		{
			end_room->closed_links[i] = 2;
		}
		i++;
	}
}

int			link_check(t_room *room, t_room *room_2)
{
	int		i;

	i = 0;
	while (room_2->next_rooms[i] != NULL)
	{
		if (room_2->next_rooms[i] == room)
			return (0);
		i++;
	}
	return (1);
}

int			*df_check(t_room *end_room)
{
	t_room	*room;
	int		i;
	int		j;
	int		*way;

	room = end_room;
	j = 1;
	way = (int*)malloc(sizeof(int) * (end_room->bf + 1));
	way[0] = end_room->bf;
	room = room->bfs_prev;
	while (room != NULL)
	{
		if (end_room->bf == room->bf + 1 && (link_check(end_room, room) == 0))
		{
			i = 0;
			while (room->next_rooms[i] != NULL)
			{
				if (room->next_rooms[i] == end_room)
				{
					room->closed_links[i] = 3;
					way[j] = i;
					j++;
					if (room->type == 0)
						room->visit++;
					close_link(end_room, room);
					end_room = room;
					break ;
				}
				i++;
			}
		}
		room = room->bfs_prev;
	}
	if (j == 1)
	{
		free(way);
		return (NULL);
	}
	else
		return (way);
}

int			short_way(t_room *rooms, t_anthill *ant, int i)
{
	t_room	*room;
	int		*way;

	room = end_room(rooms);
	if ((way = my_intrevers(df_check(room))) != NULL && i == 0)
	{
		track_record(way, ant);
		return (0);
	}
	if (i == 1)
	{
		ant->shortest_way = my_intrevers(df_check(room));
		return (0);
	}
	return (1);
}
