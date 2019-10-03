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

#include "lem-in.h"

t_room		*end_room(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->bfs_next;
	}
	return (NULL);
}

int 		size_link(t_room *room)
{
	int		size;

	size = 0;
	while (room->next_rooms[size] != NULL)
		size++;
	return (size);
}

int 		*creat_closed_links(int size)
{
	int 	*closed_links;
	int		i;

	i = 0;
	closed_links = (int*)malloc(sizeof(int) * size);
	while(i < size)
	{
		closed_links[i] = 0;
		i++;
	}
	return (closed_links);
}

void        free_closed_links(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->closed_links != 0)
			free(rooms->closed_links);
		rooms = rooms->next;
	}
}

void		close_link(t_room *end_room, t_room *room)
{
	int     i;

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

t_room      *df_check(t_room *end_room)
{
	t_room	*tmp;
	t_room	*room;
	int     i;

	tmp = NULL;
	room = end_room;
	i = 0;
	while (room->bfs_prev != NULL)
	{
		if (room->bf == room->bfs_prev->bf + 1)
		{
			tmp = room->bfs_prev;
			while (room->next_rooms[i] != NULL)
			{
				if (room->next_rooms[i] == tmp)
				{
					room->closed_links[i] = 1;
				}
				i++;
			}
		}
		room = room->bfs_prev;
	}
	room->closed_links = creat_closed_links(size_link(room));
	close_link(end_room, room);
	return(tmp);
}

void			short_way(t_room *rooms)
{
	t_room      *room;

	room = end_room(rooms);
	if (room == NULL)
	{
		ft_printf("error finding (end) room");
		exit(0);
	}
	room->closed_links = creat_closed_links(size_link(room));
	while (room->bf > 0)
	{
		room = df_check(room);
	}
//	check_link_room_full(rooms);
}