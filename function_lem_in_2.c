/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lem_in_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:21:24 by emeha             #+#    #+#             */
/*   Updated: 2019/10/10 17:21:25 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_anthill		*newanthill(void)
{
	t_anthill	*ant;

	ant = (t_anthill*)malloc(sizeof(t_anthill));
	ant->ways = (int**)malloc(sizeof(int*) * 2);
	ant->ways[0] = NULL;
	ant->ways[1] = NULL;
	ant->r_ways = NULL;
	ant->end_room = NULL;
	ant->ants = 0;
	ant->rooms = 0;
	ant->map = ft_strnew(0);
	return (ant);
}

int				check_num(char *num)
{
	int			i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i] != '\0')
	{
		if (!ft_isdigit((int)num[i]))
			return (1);
		i++;
	}
	if (i == 1 && (num[0] == '-' || num[0] == '+'))
		return (1);
	return (0);
}

int				check_room_visit(t_room *room, int size)
{
	int			i;

	i = 0;
	while (room->next_rooms[i] != NULL)
	{
		if (room->next_rooms[i]->type == 4 &&
			room->next_rooms[i]->next_rooms[0]->visit == size)
			return (1);
		else if (room->next_rooms[i]->visit == size)
			return (1);
		i++;
	}
	return (0);
}
