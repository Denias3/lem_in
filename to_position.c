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

void			add_bfs(t_room *rooms, t_room *room, int bf)
{
	if (rooms->type == 4 && rooms->bf != -1)
		add_bfs_2(rooms, bf);
	else
	{
		if (room->type == 4 && check_add_type3(room) != 0)
			return ;
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
	int	i;

	i = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		if (rooms->closed_links[i] != 1 && rooms->closed_links[i]
		!= 3 && rooms->closed_links[i] != 4 &&
				(rooms->next_rooms[i]->bf == -1 ||
				(rooms->type == 4 &&
				rooms->next_rooms[i]->type == 3)))
			add_bfs(rooms, rooms->next_rooms[i], bf);
		i++;
	}
}

int				go_bfs(t_room *rooms)
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
