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
		if (room->closed_links[i] != 1)
			size++;
		i++;
	}
	return (size);
}

static void	redirect_link(t_room *room, t_room *new_room, char *name)
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
	t_room		**tmp;
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
		if (room_in->closed_links[j] != 1)
		{
			tmp_room[i] = room_in->next_rooms[j];
			i++;
		}
		else
			redirect_link(room_in->next_rooms[j], room_out, room_in->name);
		j++;
	}
	tmp = room_out->next_rooms;
	room_out->next_rooms = tmp_room;
	free(tmp);
}

static void add_to_end(t_room *room, t_room *room_end)
{
	while (room->next != NULL)
		room = room->next;
	room->next = room_end;
}

void	rewriting_room(t_room *room_in, t_room *room_out, int count_room)
{
	room_out->name = ft_strjoin(room_in->name, ft_strdup("_out"));
	room_in->name = ft_strjoin(room_in->name, ft_strdup("_in"));
	room_out->next_rooms = room_in->next_rooms;
	room_out->closed_links = room_in->closed_links;
	room_out->type = room_in->type;
	room_out->id = count_room;

}

void	room_sharing(t_room *room_in, t_anthill *ant)
{
	t_room	*room_out;

	room_out = new_room();
	rewriting_room(room_in, room_out, ant->rooms);
	ant->rooms++;
	separation_links(room_in, room_out);
	add_to_end(room_in, room_out);
}
