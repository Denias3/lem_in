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
		rooms->bfs_prev = NULL;
		rooms->bfs_next = NULL;
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
					if (rooms->type == 4 && rooms->posit == 1)
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
					tmp->posit = 1;
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

int 			compare_room(t_room *room, t_room *compare)
{
	if ((ft_strcmp(compare->name, room->name) != 0 ||
	((room->type == 3 || room->type == 4) &&
	(compare->type == 3 || compare->type == 4))) &&
		room->posit == 0)
	{
		if ((room->type == 3 || room->type == 4) &&
			(compare->type == 3 || compare->type == 4))
			if (compare->type == room->type)
				return (0);
		return (1);
	}
	return (0);
}

void 			null_posit(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->posit = 0;
		rooms = rooms->next;
	}
}

void			rec_bf(t_room *rooms, int bf, int iter, t_room *compare)
{
	int i;
	int j;
	t_room *room_bfs;

	i = 0;
	j = 0;
	if (iter <= 0)
		return ;
	iter--;
	rooms->posit = 1;
	room_bfs = rooms;
	while (rooms->next_rooms[i] != NULL)
	{
		if (compare_room(rooms->next_rooms[i], compare) &&
				rooms->closed_links != NULL &&
				rooms->closed_links[i] != 4 &&
				rooms->closed_links[i] != 3)
		{
			if (rooms->type == 3 && rooms->closed_links[i] == 2)
			{
				if (rooms->next_rooms[i]->next_rooms[0]->bf == -1)
				{
					rooms->next_rooms[i]->next_rooms[0]->bf = bf;
					while (room_bfs->bfs_next != NULL)
						room_bfs = room_bfs->bfs_next;
					room_bfs->bfs_next = rooms->next_rooms[i]->next_rooms[0];
					rooms->next_rooms[i]->next_rooms[0]->bfs_prev = room_bfs;
				}
				if (rooms->next_rooms[i]->bf == -1)
					rooms->next_rooms[i]->bf = bf;
				else
					rec_bf(rooms->next_rooms[i], bf, iter, rooms);
			}
			else if (rooms->type != 3)
			{
				if (rooms->next_rooms[i]->bf == -1)
				{
					rooms->next_rooms[i]->bf = bf;

					if (rooms->type == 4)
					{
						while (rooms->next_rooms[i]->next_rooms[j] != NULL)
						{
							if (ft_strcmp(rooms->next_rooms[i]->next_rooms[j]->name, rooms->name) == 0)
							{
								rooms->next_rooms[i]->bfs_prev = rooms->next_rooms[i]->next_rooms[j];
								rooms->next_rooms[i]->next_rooms[j]->bfs_next = rooms->next_rooms[i];
								break ;
							}
							j++;
						}
					}
					else
					{
						while (room_bfs->bfs_next != NULL)
							room_bfs = room_bfs->bfs_next;
						room_bfs->bfs_next = rooms->next_rooms[i];
						rooms->next_rooms[i]->bfs_prev = room_bfs;
					}
				}
				else
					rec_bf(rooms->next_rooms[i], bf, iter, rooms);
			}
		}
		i++;
	}
}

int				go_bf_2(t_room *rooms)
{
	int bf;
	int iter;
	t_room *st_rooms;

	iter = 1;
	bf = 1;
	st_rooms = search_room_type(rooms, 1);
	while (end_bf(rooms) == 0)
	{
		null_posit(rooms);
		rec_bf(st_rooms, bf, iter, st_rooms);
//		print_rooms(rooms, 2);
		iter++;
		bf++;
	}
	return (0);
}

int				to_position_2(t_room *rooms)
{
	free_bf(rooms);
	if (go_bf_2(rooms) == 0)
		return (0);
	else
		return (1);
}
