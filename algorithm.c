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

int             *short_way(t_room *rooms, t_anthill *ant)
{
	int 		*way;

	way = (int*)malloc(sizeof(int) * ant->ants);

	return(way);
}

void			algorithm(t_anthill *ant, t_room *rooms)
{
	int			*way;

	way = short_way(rooms, ant);
	ant = 0;
}
