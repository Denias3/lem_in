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

t_anthill	*newanthill(void)
{
	t_anthill		*ant;

	ant = (t_anthill*)malloc(sizeof(t_anthill));
	ant->ways = (int**)malloc(sizeof(int*) * 2);
	ant->ways[0] = NULL;
	ant->ways[1] = NULL;
	ant->r_ways = NULL;
	ant->ants = 0;
	ant->max_x = 0;
	ant->max_y = 0;
	ant->rooms = 0;
	return (ant);
}
