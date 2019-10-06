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

t_room		*end_room_next(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

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

void			print_bfs(t_room *rooms)
{
	while (rooms != NULL)
	{
		ft_printf("%s-", rooms->name);
		rooms = rooms->bfs_next;
	}
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

t_room          *search_room_bf(t_room *rooms, int bf, int *baf)
{
	int i;


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
					if (rooms->type == 4 && rooms->closed_links != 0 && rooms->closed_links[i] == 2)
					{
						(*baf) = 1;
						return (rooms->next_rooms[i]);
					}
					else if (rooms->closed_links != 0 && rooms->closed_links[i] != 1 && rooms->closed_links[i] != 3)
						return (rooms->next_rooms[i]);
					else if (rooms->closed_links == 0)
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

int			go_bf(t_room *rooms)
{
	t_room	*tmp;
	t_room	*tmp2;
	int		bf;
	int 	baf;
	int     ch;

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
				tmp->bf = bf;
			else
			{
				tmp->bf = bf - baf;
				tmp->bfs_prev = tmp2;
				tmp2->bfs_next = tmp;
				tmp2 = tmp;
			}

		}
//		print_room(tmp);
	}
	tmp2->bfs_next = NULL;
	return (0);
}


int            to_position(t_room *rooms)
{
	free_bf(rooms);
	if (go_bf(rooms) == 0)
		return (0);
	else
		return (1);

}

int             ended_way(t_room *room)
{
	int         i;
	int         j;

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

int             possible_ways(t_room *room)
{
	int         j[2];

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

void            realoc_xlink(t_room *room, int position)
{
	t_room      **tmp;
	int         i;
	int         j;

	tmp = (t_room**)malloc(sizeof(t_room*) * (size_link(room)));
	i = 0;
	j = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (i != position)
		{
			tmp[j] = room->next_rooms[i];
			j++;
		}
		i++;
	}

	tmp[j] = NULL;
	free(room->next_rooms);
	room->next_rooms = tmp;
}

int             delet_xlink(t_room *room, int id)
{
	int         i;

	i = 0;
	if (room->visit > 1)
	{
		while (room->next_rooms[i] != NULL)
		{
			if (room->next_rooms[i]->id == id)
			{
				realoc_xlink(room, i);
				room->visit = 0;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

void            search_xlink(t_room *room, t_anthill *ant)
{
	int         i;
	int         j;
	int         size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if (room->type == 0 && room->visit > 1)
		{
			if (delet_xlink(room->next_rooms[ant->ways[i][j + 1]], room->id) == 0)
			{
				realoc_xlink(room, ant->ways[i][j + 1]);
				room->visit = 0;
				break ;
			}
		}
		j++;
	}
}

int             check_xlink(t_room *room, t_anthill *ant)
{
	int         i;
	int         j;
	int         size;

	i = 0;
	j = 1;
	while (ant->ways[i] != NULL)
		i++;
	i--;
	size = ant->ways[i][0];
	while (size >= j)
	{
		room = room->next_rooms[ant->ways[i][j]];
		if (room->type == 0 && room->visit > 1)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void            free_visit_close(t_room *rooms)
{
	while (rooms != NULL)
	{
		rooms->visit = 0;
		if (rooms->closed_links != NULL)
		{
			free(rooms->closed_links);
			rooms->closed_links = NULL;
		}
		rooms = rooms->next;
	}
}


//void			algorithm(t_anthill *ant, t_room *rooms)
//{
//	to_position(rooms);
//	short_way(rooms, ant);
//	rooms_sharing(rooms, ant);
//	to_position(rooms);
//
//	print_rooms(rooms, 0);
//	del_copies(rooms, ant);
//	print_rooms(rooms, 0);
////	search_xlink(rooms, ant);
////    print_vay(rooms, ant);
////    print_bfs(rooms);
////    print_rooms(rooms);
////    go_ants(rooms, ant);
//}

void			algorithm(t_anthill *ant, t_room *rooms)
{
	int         p_ways;

	while (to_position(rooms) == 0 && (p_ways = possible_ways(rooms)) > 0)
	{
		print_rooms(rooms, 0);
		del_copies(rooms, ant);
		if (short_way(rooms, ant) == 0)
		{
			if (check_xlink(rooms, ant) == 1)
			{
				search_xlink(rooms, ant);
//				print_rooms(rooms, 0);
				null_track_record(ant);
				free_visit_close(rooms);
			}
			else
				rooms_sharing(rooms, ant);
		}
	}
	del_copies(rooms, ant);
	print_rooms(rooms, 1);
}
