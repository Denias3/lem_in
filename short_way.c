/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 01:18:18 by fschille          #+#    #+#             */
/*   Updated: 2019/09/30 01:18:23 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			link_check(t_room *room, t_room *room_2)
{
	int		i;

	i = 0;
	while (room_2->next_rooms[i] != NULL)
	{
		if (ft_strcmp(room_2->next_rooms[i]->name, room->name) == 0 &&
		room_2->closed_links[i] != 1 && room_2->closed_links[i] != 4 &&
		room_2->closed_links[i] != 3)
			return (1);
		else if (ft_strcmp(room_2->next_rooms[i]->name, room->name) == 0 &&
		room_2->closed_links[i] != 4 && room_2->closed_links[i] != 3)
			return (2);
		i++;
	}
	return (0);
}

void		df_check2(t_room **end_room, t_room *room, int *way, int *j)
{
	int i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (ft_strcmp(room->next_rooms[i]->name, (*end_room)->name) == 0)
		{
			if ((*end_room)->type == 3 &&
				check_room_visit((*end_room), 2) == 0 &&
			room->closed_links[i] != 2)
				return ;
			room->closed_links[i] = 3;
			way[(*j)] = i;
			(*j)++;
			if (room->type == 0 || room->type == 3 || room->type == 4)
				room->visit++;
			close_link(*end_room, room);
			*end_room = room;
			return ;
		}
		i++;
	}
}

int			*df_check(t_room *end_room)
{
	t_room	*room;
	t_room	*tmp;
	int		check;
	int		j;
	int		*way;

	room = end_room;
	check = 0;
	way = (int*)malloc(sizeof(int) * (end_room->bf + 1));
	way[0] = end_room->bf;
	room = room->bfs_prev;
	j = 1;
	while (room != NULL)
	{
		tmp = room;
		while (check == 0 && end_room->bf == tmp->bf + 1)
		{
			if (link_check(end_room, tmp) == 1)
				check = 1;
			tmp = tmp->bfs_prev;
		}
		if (check == 1 && end_room->bf == room->bf + 1 &&
			(link_check(end_room, room) == 1))
			df_check2(&end_room, room, way, &j);
		if (check == 0 && end_room->bf == room->bf + 1 &&
			(link_check(end_room, room) == 2))
			df_check2(&end_room, room, way, &j);
		check = 0;
		room = room->bfs_prev;
	}
	if ((j - 1) == way[0])
		return (way);
	else
	{
		free(way);
		return (NULL);
	}
}

int			short_way(t_room *rooms, t_anthill *ant, int i)
{
	t_room	*room;
	int		*way;

	room = end_rooms(rooms);
	if (i == 0 && (way = my_intrevers(df_check(room))) != NULL)
	{
		track_record(way, ant);
		return (0);
	}
	else if (i == 1)
	{
		ant->shortest_way = my_intrevers(df_check(room));
		return (0);
	}
	return (1);
}
