/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_record.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:11:32 by fschille          #+#    #+#             */
/*   Updated: 2019/10/02 14:11:34 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void        track_record(int *way, t_anthill *ant)
{
	int     i;

	i = 0;
	if (!ant->ways)
	{
		ant->ways = (int**)malloc(sizeof(int*) * 2);
		ant->ways[0] = way;
		ant->ways[1] = NULL;
	}
}