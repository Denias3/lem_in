/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 11:37:18 by emeha             #+#    #+#             */
/*   Updated: 2019/10/02 11:37:21 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int         check_go_room(t_room *rooms, int *way)
{
    int     i;

    i = 1;
    while (i - 1 <= way[0])
    {
        if (rooms->next_rooms[way[i]]->state > 0 && (rooms->type == 0 || rooms->type == 1))
            return (0);
        rooms = rooms->next_rooms[way[i]];
        i++;
    }
    return (1);
}

void        go_way(t_room *st_rooms, int *way)
{
    t_room  *room;
    int i;

    i = 1;
    room = st_rooms;
    while (i - 1 <= way[0])
    {
        room->next_rooms[way[i]]->state++;
        room->state--;
        room = room->next_rooms[way[i]];
        i++;
    }
}

void    go_ants(t_room *rooms, t_anthill *ant)
{
    t_room *st_room;

	st_room = search_room_type(rooms, 1);
	st_room->state = ant->rooms;
    while (st_room->state > 0)
    {

    }
}