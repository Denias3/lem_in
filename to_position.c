/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 16:39:22 by emeha             #+#    #+#             */
/*   Updated: 2019/10/06 16:39:24 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ch_bf(t_room *room)
{
	int			i;

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

t_room			*search_room_bf(t_room *rooms, int bf, int *baf)
{
	int			i;

	while (rooms != NULL)
	{
		i = 0;
		if (rooms->bf == bf && ch_bf(rooms) == 0)
		{
			while (rooms->next_rooms[i] != NULL)
			{
				(*baf) = 0;
				if (rooms->next_rooms[i]->bf == -1)
				{
					if (rooms->type == 4 && rooms->visit == 1)
						break ;
					else if (rooms->type == 4 && rooms->closed_links != 0 && rooms->closed_links[i] == 2)
					{
						(*baf) = 1;
						return (rooms->next_rooms[i]);
					}
					else if (rooms->closed_links != 0 && (rooms->closed_links[i] == 0 || rooms->closed_links[i] == 2))
						return (rooms->next_rooms[i]);
					else if (rooms->closed_links == 0)
						return (rooms->next_rooms[i]);

				}
				i++;
			}
		}
		else if (rooms->next_rooms[0] == NULL && rooms->bf == -1)
		{
			rooms->type = 5;
			rooms->bf = 0;
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

int				go_bf(t_room *rooms)
{
	t_room		*tmp;
	t_room		*tmp2;
	int			bf;
	int			baf;
	int			ch;

	ch = 0;
	baf = 0;
	tmp2 = search_room_type(rooms, 1);
	bf = 1;
	while (end_bf(rooms) == 0)
	{
		tmp = search_room_bf(rooms, bf - 1, &baf);
		if (ch == 2)
			return (1);
		if (tmp == NULL)
		{
			ch++;
			bf++;
		}
		else
		{
			ch = 0;
			if (tmp->type == 4)
			{
				if (tmp->next_rooms[0]->bf != -1)
					tmp->visit = 1;
				tmp->bf = bf;
			}
			else
			{
				tmp->bf = bf - baf;
				tmp->bfs_prev = tmp2;
				tmp2->bfs_next = tmp;
				tmp2 = tmp;
			}
		}
	}
	tmp2->bfs_next = NULL;
	return (0);
}

int				to_position(t_room *rooms)
{
	free_bf(rooms);
	if (go_bf(rooms) == 0)
		return (0);
	else
		return (1);
}
