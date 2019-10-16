/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_sharing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 11:25:06 by emeha             #+#    #+#             */
/*   Updated: 2019/10/03 11:25:07 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		size_links(t_room *room)
{
	int			i;
	int			size;

	size = 1;
	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->closed_links == NULL || room->closed_links[i] != 1)
			size++;
		i++;
	}
	return (size);
}

static void		separation_links(t_room *room_in, t_room *room_out)
{
	t_room		**tmp_room;
	int			size;
	int			i[2];

	i[1] = 0;
	i[0] = 1;
	size = size_links(room_in);
	tmp_room = (t_room**)malloc(sizeof(t_room*) * size);
	room_out->closed_links = (int*)malloc(sizeof(int) * size);
	tmp_room[0] = room_in;
	room_out->closed_links[0] = 2;
	while (room_in->next_rooms[i[1]] != NULL)
	{
		if (room_in->closed_links[i[1]] == 0)
		{
			room_out->closed_links[i[0]] = 0;
			tmp_room[i[0]] = room_in->next_rooms[i[1]];
			i[0]++;
		}
		else if (room_in->closed_links[i[1]] == 3)
			redirect_link(room_in->next_rooms[i[1]], room_out, room_in->name);
		i[1]++;
	}
	tmp_room[i[0]] = NULL;
	room_out->next_rooms = tmp_room;
}

static void		add_to_end(t_room *room, t_room *room_end)
{
	while (room->next != NULL)
		room = room->next;
	room->next = room_end;
}

void			room_sharing(t_room *room_in, t_anthill *ant)
{
	t_room		*room_out;

	room_out = new_room();
	free(room_out->next_rooms);
	rewriting_room(room_in, room_out, ant->rooms);
	ant->rooms++;
	separation_links(room_in, room_out);
	close_link_in(room_in);
	add_to_end(room_in, room_out);
}

void			rooms_sharing(t_room *room, t_anthill *ant)
{
	int			i;
	int			j;
	t_room		*st_room;

	j = 0;
	i = 1;
	st_room = search_room_type(room, 1);
	while (ant->ways[j] != NULL)
		j++;
	j--;
	while (i < ant->ways[j][0])
	{
		st_room = st_room->next_rooms[ant->ways[j][i]];
		room_sharing(st_room, ant);
		i++;
	}
}
