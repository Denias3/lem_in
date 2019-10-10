/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:09:55 by emeha             #+#    #+#             */
/*   Updated: 2019/10/10 17:09:57 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			memolloc_room(t_room *room1, t_room *room2, int i)
{
	t_room		**tmp_room;
	t_room		**tmp;
	int			size;
	int			j;

	size = i + 2;
	tmp_room = (t_room**)malloc(sizeof(t_room*) * size);
	j = 0;
	while (size > 2)
	{
		tmp_room[j] = room1->next_rooms[j];
		j++;
		size--;
	}
	tmp_room[j] = room2;
	j++;
	tmp_room[j] = NULL;
	tmp = room1->next_rooms;
	room1->next_rooms = tmp_room;
	free(tmp);
}

t_room			*check_name(t_room *rooms, char *name)
{
	while (rooms != NULL)
	{
		if (ft_strcmp(rooms->name, name) == 0)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}
