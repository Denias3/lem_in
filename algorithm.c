/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 04:35:24 by fschille          #+#    #+#             */
/*   Updated: 2019/09/12 04:35:26 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_room          *search_room_type(t_room *rooms, short type)
{
    while (rooms != NULL)
    {
        if (rooms->type == type)
			return (rooms);
		rooms = rooms->next;
    }
    return (NULL);
}

int 			ch_bf(t_room *room)
{
	int i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->next_rooms[i]->bf == -1)
			return (0);
		i++;
	}
	return (1);
}

void			free_bf(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 1)
			rooms->bf = 0;
		else
			rooms->bf = -1;
		rooms = rooms->next;
	}
}

t_room          *search_room_bf(t_room *rooms, int bf)
{
	int i;

	i = 0;
	while (rooms != NULL)
	{
		if (rooms->bf == bf && ch_bf(rooms) == 0)
		{
			while (rooms->next_rooms[i] != NULL)
			{
				if (rooms->next_rooms[i]->bf == -1)
				{
					if (rooms->closed_links != NULL && rooms->closed_links[i] == 0)
						return (rooms->next_rooms[i]);
					else if (rooms->closed_links == NULL)
						return (rooms->next_rooms[i]);
				}

				i++;
			}
		}
		rooms = rooms->next;
	}
	return (NULL);
}

int				end_bf(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->bf == -1)
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

void			go_bf(t_room *rooms)
{
	t_room *tmp;
	int bf;

	bf = 1;
	while (end_bf(rooms) == 0)
	{
		tmp = search_room_bf(rooms, bf - 1);
		if (tmp == NULL)
			bf++;
		else
			tmp->bf = bf;
	}
}

void            to_position(t_room *rooms)
{
	free_bf(rooms);
	go_bf(rooms);
}


void			algorithm(t_anthill *ant, t_room *rooms)
{
	ant = NULL;
    to_position(rooms);
	short_way(rooms);
//	to_position(rooms);
	print_rooms(rooms);
//	go_ants(rooms, ant);
}

