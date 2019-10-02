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
		rooms = rooms->next;
	}
	return (NULL);
}

int 		size_link(t_room *rooms)
{
	int		size;

	size = 0;
	while (rooms->next_rooms[size] != NULL)
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
	int     i;

	i = 0;
	while (rooms != NULL)
	{
		if (rooms->closed_links != 0)
			free(rooms->closed_links);
		rooms = rooms->next;
	}
}

void		close_link(t_room *room, t_room *tmp)
{
	int     i;

	i = 0;
	while (tmp->next_rooms[i] != NULL)
	{
		if (tmp->next_rooms[i] == room)
		{
			tmp->closed_links[i] = 1;
		}
		i++;
	}
}

t_room      *df_check(t_room *end_room)
{
	t_room	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (end_room->next_rooms[i] != NULL)
	{
		if (end_room->bf == end_room->next_rooms[i]->bf && tmp == NULL)
			tmp = end_room->next_rooms[i];
		if (end_room->bf == end_room->next_rooms[i]->bf + 1)
			tmp = end_room->next_rooms[i];
		i++;
	}
	tmp->closed_links = creat_closed_links(size_link(tmp));
	close_link(end_room, tmp);
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
	while (room->bf > 0)
	{
		room = df_check(room);
	}
//	check_link_room_full(rooms);
}