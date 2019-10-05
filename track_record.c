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

void        free_track_record(t_anthill *ant)
{
	int     i;

	i = 0;
	while (ant->ways[i] != NULL)
	{
		free(ant->ways[i]);
		i++;
	}
	free(ant->ways);
	free(ant);
}

static int         len_int(int **way)
{
	int     i;

	i = 0;
	while (way[i] != NULL)
	{
		i++;
	}
	return (i + 1);
}

void        track_record(int *way, t_anthill *ant)
{
	int     **ways;
	int     i;

	ways = NULL;
	i = 0;
	if (!ant->ways)
	{
		ant->ways = (int**)malloc(sizeof(int*) * 2);
		ant->ways[0] = way;
		ant->ways[1] = NULL;
	}
	else
	{
		ways = (int**)malloc(sizeof(int*) * (len_int(ant->ways) + 1));
		while (ant->ways[i] != NULL)
		{
			ways[i] = ant->ways[i];
			i++;
		}
		ways[i] = way;
		ways[i + 1] = NULL;
		free(ant->ways);
		ant->ways = ways;
	}
}