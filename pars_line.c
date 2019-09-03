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
**			number_of_ants - 0
**			the_room       - 1
**			the_link       - 2
**			command:
**				##start    - 4
**				##end      - 5
*/

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

int		pars_line(t_anthill *ant, t_room *room, char *line, int type)
{
    char **split;
	t_room *rooms;

    if (type == 0)
    {
		ant->ants = ft_atoi(line);
        return (1);
    }
    else if (type == 1 || type == 4 || type == 5)
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
        if (type == 4)
            room->type = 1;
        else if (type == 5)
            room->type = 2;
        else
            room->type = 0;
		if (check_name_coord(rooms, room) == 0)
			error();
        return (1);
    }
//    else if (type == 2)
//    {
//
//    }
    else
        return (-1);
}