/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 16:39:22 by emeha             #+#    #+#             */
/*   Updated: 2019/10/06 16:39:24 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_bf(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->bfs_prev = NULL;
		rooms->bfs_next = NULL;
		if (rooms->type == 1)
			rooms->bf = 0;
		else
			rooms->bf = -1;
		rooms = rooms->next;
	}
}

void			next_bfs_type4(t_room *rooms, t_room *room, int bf)
{
	int 		i;

	i = 1;
	while (room->next_rooms[i] != NULL)
	{
		if (room->closed_links[i] == 0 &&
			room->next_rooms[i]->bf == -1)
		{
			while (rooms->bfs_next != NULL)
				rooms = rooms->bfs_next;
			rooms->bfs_next = room->next_rooms[i];
			room->next_rooms[i]->bfs_prev = rooms;
			rooms->bfs_next->bf = bf;
		}
		i++;
	}
}

int 			check_add_type3(t_room *room)
{
	int 		i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->closed_links[i] == 2 && room->next_rooms[i]->bf == -1)
			return (0);
		i++;
	}
	return (1);
}

void			add_bfs(t_room *rooms, t_room *room, int bf)
{
	t_room *tmp;

	if (rooms->type == 4 && rooms->bf != -1)
	{
		tmp = rooms->bfs_prev;
		tmp->bfs_next = rooms->next_rooms[0];
		rooms->next_rooms[0]->bfs_prev = tmp;
		rooms->next_rooms[0]->bf = rooms->bf;
		rooms->next_rooms[0]->link_in = rooms;
		tmp = rooms;
		if (tmp->bfs_next != NULL)
		{
			tmp->bfs_next->bfs_prev = tmp->next_rooms[0];
			tmp->next_rooms[0]->bfs_next = tmp->bfs_next;
		}
		next_bfs_type4(rooms->next_rooms[0], rooms, bf);
		rooms->bfs_next = rooms->next_rooms[0]->bfs_next;
	}
	else
	{
		if (room->type == 4 && check_add_type3(room) != 0)
			return;
		while (rooms->bfs_next != NULL)
			rooms = rooms->bfs_next;
		rooms->bfs_next = room;
		room->bfs_prev = rooms;
		room->bf = bf;
		if (room->type == 4 && room->next_rooms[0]->bf == -1)
			room->next_rooms[0]->bf = bf;
	}
}

void			next_bfs(t_room *rooms, int bf)
{
	int 		i;

	i = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		if (rooms->closed_links[i] != 1 && rooms->closed_links[i] != 3 && rooms->closed_links[i] != 4 &&
				(rooms->next_rooms[i]->bf == -1 || (rooms->type == 4 && rooms->next_rooms[i]->type == 3)))
			add_bfs(rooms, rooms->next_rooms[i], bf);
		i++;
	}
}

int 			go_bfs(t_room *rooms)
{
	rooms = search_room_type(rooms, 1);
	while (rooms != NULL && rooms->type != 2)
	{
		next_bfs(rooms, rooms->bf + 1);
		rooms = rooms->bfs_next;
	}
	if (rooms == NULL)
		return (1);
	rooms->bfs_next = NULL;
	return (0);
}

int				to_position_2(t_room *rooms)
{
	free_bf(rooms);
	if (go_bfs(rooms) == 0)
		return (0);
	else
		return (1);
}
