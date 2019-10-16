/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:41:43 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 17:02:34 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					main(void)
{
	t_anthill		*ant;
	t_room			*rooms;

	rooms = new_room();
	ant = newanthill();
	validation(ant, rooms);
	algorithm(ant, rooms);
	free_track_record(ant);
	free_rooms(rooms);
	return (0);
}
