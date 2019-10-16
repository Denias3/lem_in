/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:10:15 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 12:10:17 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*my_intrevers(int *way)
{
	int		i;
	int		tmp;
	int		m_i;

	if (way == NULL)
		return (NULL);
	i = 1;
	m_i = way[0];
	while (i < m_i)
	{
		tmp = way[i];
		way[i] = way[m_i];
		way[m_i] = tmp;
		i++;
		m_i--;
	}
	return (way);
}

t_room		*end_rooms(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

int			size_link(t_room *room)
{
	int		size;

	size = 0;
	while (room->next_rooms[size] != NULL)
		size++;
	return (size);
}

int			*creat_closed_links(int size)
{
	int		*closed_links;
	int		i;

	i = 0;
	closed_links = (int*)malloc(sizeof(int) * size);
	while (i < size)
	{
		closed_links[i] = 0;
		i++;
	}
	return (closed_links);
}

void		close_link(t_room *end_room, t_room *room)
{
	int	i;

	i = 0;
	while (end_room->next_rooms[i] != NULL)
	{
		if (end_room->next_rooms[i] == room)
			end_room->closed_links[i] = 2;
		i++;
	}
}
