/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_sharing_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:33:42 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 12:33:43 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			redirect_link(t_room *room, t_room *new_room, char *name)
{
	int			i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (ft_strcmp(room->next_rooms[i]->name, name) == 0)
		{
			room->next_rooms[i] = new_room;
			break ;
		}
		i++;
	}
}

void			rewriting_room(t_room *room_in,
		t_room *room_out, int count_room)
{
	room_out->name = ft_strdup(room_in->name);
	room_out->next_rooms = room_in->next_rooms;
	room_out->closed_links = room_in->closed_links;
	room_out->visit = room_in->visit;
	room_out->type = 4;
	room_in->type = 3;
	room_out->id = count_room;
}

void			close_link_in(t_room *room_in)
{
	int			i;

	i = 0;
	while (room_in->next_rooms[i] != NULL)
	{
		if (room_in->closed_links[i] == 0)
			room_in->closed_links[i] = 1;
		i++;
	}
}
