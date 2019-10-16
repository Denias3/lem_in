/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lem-in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:02:06 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 17:56:09 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				count_char_double_array(char **str)
{
	int			i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			free_char_double_array(char **str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_room			*new_room(void)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = NULL;
	room->id = -1;
	room->type = -1;
	room->state = 0;
	room->x = -1;
	room->y = -1;
	room->bf = -1;
	room->closed_links = NULL;
	room->link_in = NULL;
	room->visit = 0;
	room->posit = 0;
	room->next = NULL;
	room->next_rooms = (t_room**)malloc(sizeof(t_room*) * 1);
	room->next_rooms[0] = NULL;
	room->next_rooms[1] = NULL;
	room->bfs_next = NULL;
	room->bfs_prev = NULL;
	return (room);
}

void			free_rooms(t_room *rooms)
{
	t_room		*tmp;

	while (rooms != NULL)
	{
		if (rooms->closed_links != NULL)
		{
			free(rooms->closed_links);
			rooms->closed_links = NULL;
		}
		free(rooms->next_rooms);
		free(rooms->name);
		tmp = rooms;
		rooms = rooms->next;
		free(tmp);
	}
}

void			error(char *text)
{
	ft_printf("error (%s)\n", text);
	exit(0);
}
