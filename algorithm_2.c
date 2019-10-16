/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:41:30 by fschille          #+#    #+#             */
/*   Updated: 2019/10/16 11:41:32 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*end_room_next(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

t_room			*search_room_type(t_room *rooms, short type)
{
	while (rooms != NULL)
	{
		if (rooms->type == type)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

int				ended_way(t_room *room)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->next_rooms[i]->visit == 0)
			j++;
		i++;
	}
	return (j);
}

int				possible_ways(t_room *room)
{
	int			j[2];

	j[0] = ended_way(room);
	room = end_room_next(room);
	j[1] = ended_way(room);
	if (j[0] > 0 && j[1] > 0)
	{
		return (j[0] < j[1] ? j[0] : j[1]);
	}
	else
		return (0);
}

t_room			*search_start_room(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 1)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}
