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

#include "lem-in.h"

/*
**			pars_line
**		arg: (type)
**			the_room       - 1
**			the_link       - 2
**			command:
**				##start    - 4
**				##end      - 5
*/

void			check_link_room(t_room *room)
{
	int i;

	i = 0;
	ft_printf("%s - room\n", room->name);
	ft_printf("%d - df\n", room->bf);
	ft_printf("%d - type\n", room->type);
	ft_printf("links:\n");
	while(room->next_rooms[i] != NULL)
	{
		ft_printf("%4s - name\n", room->next_rooms[i]->name);
		i++;
	}
	ft_printf("\n");
}

void 			memolloc_room(t_room *room1, t_room *room2, int i)
{
	t_room		**tmp_room;
	t_room		**tmp;
	int 		size;
	int 		j;

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

static int		check_name_coord(t_room *rooms, t_room *room)
{
	int ch;

	ch = 0;
	while (rooms != NULL)
	{
		if (ft_strcmp(rooms->name, room->name ) == 0 || 
			(rooms->x == room->x && rooms->y == room->y))
			ch++;
		if (ch >= 2)
			return (0);
		rooms = rooms->next;
	}
	return (1);
}

t_room   *check_name(t_room *rooms, char *name)
{
    while (rooms != NULL)
    {
        if (ft_strcmp(rooms->name, name) == 0)
            return (rooms);
        rooms = rooms->next;
    }
    return (NULL);
}

int				pars_line_room(t_anthill *ant, t_room *room, char *line, t_var_valid *v_val)
{
    char **split;
    t_room *rooms;

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
        split = ft_strsplit(line, ' ');
        room->name = split[0];
        room->x = ft_atoi(split[1]);
        room->y = ft_atoi(split[2]);
        free(split[1]);
        free(split[2]);
        free(split);
        if (v_val->type_past == 4)
            room->type = 1;
        else if (v_val->type_past == 5)
            room->type = 2;
        else
            room->type = 0;
        if (check_name_coord(rooms, room) == 0)
            error();
        return (1);
    }
    else
        return (-1);
}

void			check_link_room_full(t_room *room)
{
	ft_printf("------------------------\n");
	while (room != NULL)
	{
		check_link_room(room);
		room = room->next;
	}
	ft_printf("------------------------\n");
}

int				pars_line_link(t_room *room, char *line)
{
    char		**split;
	t_room		*room1;
	t_room		*room2;
	int 		i;

	i = 1;
    split = ft_strsplit(line, '-');
    if ((room1 = check_name(room, split[0])) != NULL && (room2 = check_name(room, split[1])) != NULL)
    {

    	free(split[0]);
    	free(split[1]);
    	free(split);
		if (room1->next_rooms[0] == NULL)
		{
			room1->next_rooms[0] = room2;
		}
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
			memolloc_room(room2, room1 , i);
		}
//		check_link_room_full(room);
		return (0);
    }
    else
    	return (1);
}
