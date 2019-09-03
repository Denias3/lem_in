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

#include "lem-in.h"

static t_anthill	*newanthill(void)
{
	t_anthill *ant;

	ant = (t_anthill*)malloc(sizeof(t_anthill));
	ant->ants = 0;
	ant->max_x = 0;
	ant->max_y = 0;
	ant->rooms = 0;
	return (ant);
}

int					main(void)
{
	t_anthill *ant;

	ant = newanthill();
	validation(ant);
	free(ant);
	return (0);
}
