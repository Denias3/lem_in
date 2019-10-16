/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:43:25 by fschille          #+#    #+#             */
/*   Updated: 2019/10/16 11:43:27 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				delet_xlink(t_room *room, int id)
{
	int			i;

	i = 0;
	if (room->visit > 1)
	{
		while (room->next_rooms[i] != NULL)
		{
			if (room->next_rooms[i]->id == id)
			{
				room->closed_links[i] = 4;
				room->visit = 0;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void			search_xlink(t_room *room, t_anthill *ant)
{
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 0;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	while (size >= ++j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if ((room->type == 0 || room->type == 3 || room->type == 4) &&
			room->visit > 1)
		{
			if (delet_xlink(room->next_rooms[ant->ways[i][j + 1]],
							room->id) == 0)
			{
				room->closed_links[ant->ways[i][j + 1]] = 4;
				room->visit = 0;
				break ;
			}
		}
	}
}

int				check_xlink(t_room *room, t_anthill *ant)
{
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	room = search_start_room(room);
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if ((room->type == 0 || room->type == 3 || room->type == 4)
			&& room->visit > 1)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void			null_visit_close(t_room *rooms)
{
	int			i;
	int			size;

	while (rooms != NULL)
	{
		i = 0;
		rooms->visit = 0;
		size = size_link(rooms);
		while (size > i)
		{
			if (rooms->closed_links[i] != 4)
				rooms->closed_links[i] = 0;
			i++;
		}
		rooms = rooms->next;
	}
}

void			all_creat_closed_links(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->closed_links = creat_closed_links(size_link(rooms));
		rooms = rooms->next;
	}
}
