/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:35:11 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 18:37:23 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			pars_line
**		arg: (type)
**			the_room       - 1
**			the_link       - 2
**			command:
**				##start    - 4
**				##end      - 5
*/

static int		check_name_coord(t_room *rooms, t_room *room)
{
	int			ch;

	ch = 0;
	while (rooms != NULL)
	{
		if (ft_strcmp(rooms->name, room->name) == 0 ||
			(rooms->x == room->x && rooms->y == room->y))
			ch++;
		if (ch >= 2)
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

static void		pars_line_room_2(t_anthill *ant, t_room *room,
				char *line, t_var_valid *v_val)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	room->name = split[0];
	memaloc_map_rooms(ant, split[0]);
	if (check_num(split[1]) == 1|| check_num(split[2]) == 1)
		error("no valid room");
	room->x = ft_atoi(split[1]);
	room->y = ft_atoi(split[2]);
	room->id = ant->rooms - 1;
	free(split[1]);
	free(split[2]);
	free(split);
	if (v_val->type_past == 4)
		room->type = 1;
	else if (v_val->type_past == 5)
		room->type = 2;
	else
		room->type = 0;
}

int				pars_line_room(t_anthill *ant, t_room *room,
				char *line, t_var_valid *v_val)
{
	t_room		*rooms;

	if (v_val->type == 1 || v_val->type == 4 || v_val->type == 5)
	{
		rooms = room;
		ant->rooms++;
		while (room != NULL && room->name != NULL)
		{
			if (room->next == NULL)
			{
				room->next = new_room();
				room = room->next;
				break ;
			}
			room = room->next;
		}
		pars_line_room_2(ant, room, line, v_val);
		if (check_name_coord(rooms, room) == 0)
			error("two rooms with the same coordinates");
		return (1);
	}
	else
		return (-1);
}

void			pars_line_link_2(t_room *room1, t_room *room2, int i)
{
	if (room1->next_rooms[0] == NULL)
		room1->next_rooms[0] = room2;
	else
	{
		while (room1->next_rooms[i] != NULL)
			i++;
		memolloc_room(room1, room2, i);
	}
	i = 1;
	if (room2->next_rooms[0] == NULL)
		room2->next_rooms[0] = room1;
	else
	{
		while (room2->next_rooms[i] != NULL)
			i++;
		memolloc_room(room2, room1, i);
	}
}

int				pars_line_link(t_room *room, char *line)
{
	char		**split;
	t_room		*room1;
	t_room		*room2;

	split = ft_strsplit(line, '-');
	if ((room1 = check_name(room, split[0], split[1])) != NULL &&
		(room2 = check_name(room, split[1], split[0])) != NULL &&
		ft_strcmp(split[0], split[1]) != 0)
	{
		free(split[0]);
		free(split[1]);
		free(split);
		pars_line_link_2(room1, room2, 1);
		return (0);
	}
	else
	{
		free(split[0]);
		free(split[1]);
		free(split);
		return (1);
	}
}

int				pars_line_link_new(char *line, t_anthill *ant)
{
	char		**split;

	split = ft_strsplit(line, '-');
	if (check_name_2(split[0], split[1], ant) &&
		ft_strcmp(split[0], split[1]) != 0)
	{
		memaloc_map_links(ant, line);
		free(split[0]);
		free(split[1]);
		free(split);
		return (0);
	}
	else
	{
		free(split[0]);
		free(split[1]);
		free(split);
		return (1);
	}
}
