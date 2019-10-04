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

#include "lem-in.h"

static int size_links(t_room *room)
{
	int i;
	int size;

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

void	redirect_link(t_room *room, t_room *new_room, char *name)
{
	int i;

	i = 0;
	while(room->next_rooms[i] != NULL)
	{
		if (ft_strcmp(room->next_rooms[i]->name,name) == 0)
		{
			room->next_rooms[i] = new_room;
			break ;
		}
		i++;
	}
}

static void separation_links(t_room *room_in, t_room *room_out)
{
	t_room		**tmp_room;
	int 		size;
	int 		i;
	int 		j;

	j = 0;
	i = 1;
	size = size_links(room_in);
	tmp_room = (t_room**)malloc(sizeof(t_room*) * size);
	tmp_room[0] = room_in;
	while (room_in->next_rooms[j] != NULL)
	{
		if (room_in->closed_links[j] == 0)
		{
			tmp_room[i] = room_in->next_rooms[j];
			i++;
		}
		else if (room_in->closed_links[j] == 3)
			redirect_link(room_in->next_rooms[j], room_out, room_in->name);
		j++;
	}
	tmp_room[i] = NULL;
	room_out->next_rooms = tmp_room;
	if (room_out->closed_links != NULL)
		room_out->closed_links = NULL;

}

static void add_to_end(t_room *room, t_room *room_end)
{
	while (room->next != NULL)
		room = room->next;
	room->next = room_end;
}

void	rewriting_room(t_room *room_in, t_room *room_out, int count_room)
{
	room_out->name = ft_strdup(room_in->name);
	room_out->next_rooms = room_in->next_rooms;
	room_out->closed_links = room_in->closed_links;
	room_out->type = 4;
	room_in->type = 3;
	room_out->id = count_room;

}

void	close_link_in(t_room *room_in)
{
	int i;

	i = 0;
	while (room_in->next_rooms[i] != NULL)
	{
		if (room_in->closed_links[i] == 0)
			room_in->closed_links[i] = 1;
		i++;

	}
}

void	room_sharing(t_room *room_in, t_anthill *ant)
{
	t_room	*room_out;

	room_out = new_room();
	free(room_out->next_rooms);
	rewriting_room(room_in, room_out, ant->rooms);
	ant->rooms++;
	separation_links(room_in, room_out);
//	print_close_links(room_out);
//	print_close_links(room_in);
	close_link_in(room_in);
//	print_close_links(room_out);
//	print_close_links(room_in);
	add_to_end(room_in, room_out);
}

void	rooms_sharing(t_room *room, t_anthill *ant)
{
	int i;
	t_room *st_room;

	i = 1;
	st_room = search_room_type(room, 1);
	while (i < ant->ways[0][0])
	{
		st_room = st_room->next_rooms[ant->ways[0][i]];
		room_sharing(st_room, ant);
		i++;
	}
}
