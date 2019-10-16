/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_position_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:58:24 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 11:58:26 by emeha            ###   ########.fr       */
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
	int	i;

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

int				check_add_type3(t_room *room)
{
	int	i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->closed_links[i] == 2 && room->next_rooms[i]->bf == -1)
			return (0);
		i++;
	}
	return (1);
}

void			add_bfs_2(t_room *rooms, int bf)
{
	t_room *tmp;

	tmp = rooms->bfs_prev;
	tmp->bfs_next = rooms->next_rooms[0];
	rooms->next_rooms[0]->bfs_prev = tmp;
	rooms->next_rooms[0]->bf = rooms->bf;
	tmp = rooms;
	if (tmp->bfs_next != NULL)
	{
		tmp->bfs_next->bfs_prev = tmp->next_rooms[0];
		tmp->next_rooms[0]->bfs_next = tmp->bfs_next;
	}
	next_bfs_type4(rooms->next_rooms[0], rooms, bf);
	rooms->bfs_next = rooms->next_rooms[0]->bfs_next;
}
