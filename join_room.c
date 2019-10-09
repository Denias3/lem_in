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

#include "lem_in.h"

int			search_redirect_link(t_room *room, char *name)
{
	int i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (ft_strcmp(room->next_rooms[i]->name, name) == 0 && room->next_rooms[i]->type == 4)
			return (i);
		i++;
	}
	return (-1);
}

void		del_copies(t_room *rooms, t_anthill *ant)
{
	t_room	*tmp;
	t_room	*tmp2;
	int		i;
	int		red;

	red = -1;
	while (rooms != NULL)
	{
		if (rooms->type == 4)
		{
			if (rooms->closed_links != NULL)
			{
				free(rooms->closed_links);
				rooms->closed_links = NULL;
			}
			tmp2->next = NULL;
			free(rooms->next_rooms);
			free(rooms->name);
			ant->rooms--;
			tmp = rooms;
			rooms = rooms->next;
			free(tmp);
			continue ;
		}
		else if (rooms->type == 3)
		{
			i = 0;
			while (rooms->next_rooms[i] != NULL)
			{
				if ((red = search_redirect_link(rooms->next_rooms[i], rooms->name)) != -1)
					rooms->next_rooms[i]->next_rooms[red] = rooms;
				else if (rooms->closed_links[i] == 1)
					rooms->closed_links[i] = 0;
				i++;
			}
			rooms->type = 0;
		}
		tmp2 = rooms;
		rooms = rooms->next;
	}
}
