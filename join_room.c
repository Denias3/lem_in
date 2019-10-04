/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 15:09:24 by emeha             #+#    #+#             */
/*   Updated: 2019/10/03 15:09:26 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	del_copies(t_room *rooms, t_anthill *ant)
{
	t_room	*tmp;
	t_room	*tmp2;

	while (rooms != NULL)
	{
		if (rooms->closed_links != NULL)
		{
			free(rooms->closed_links);
			rooms->closed_links = NULL;
		}
		if (rooms->type == 4)
		{
			tmp2->next = NULL;
			free(rooms->next_rooms);
			free(rooms->name);
			ant->rooms--;
			tmp = rooms;
			rooms = rooms->next;
			free(tmp);
			continue ;
		}
		tmp2 = rooms;
		rooms = rooms->next;
	}
}

void	join_rooms(t_room *rooms)
{
	int i;

	while (rooms->next != NULL)
	{
		if (rooms->type == 3)
		{
			i = 0;
			while (rooms->next_rooms[i] != NULL)
			{
				if (rooms->closed_links[i] == 3)
					redirect_link(rooms->next_rooms[i], rooms, rooms->name);
				i++;
			}
			rooms->type = 0;
		}
		if (rooms->visit == 1)
			rooms->visit = 0;
		rooms = rooms->next;
	}
}

void	join_rooms_main(t_room *rooms, t_anthill *ant)
{
	join_rooms(rooms);
	del_copies(rooms, ant);
}

