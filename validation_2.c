/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:23 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 11:18:24 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				validation_2(t_anthill *ant, t_room *rooms,
		t_var_valid *var_valid, char *line)
{
	if (var_valid->stage == 0)
		stage_num_ant(var_valid, ant, line);
	else if (var_valid->stage == 1 && var_valid->type != 2)
		stage_rooms(var_valid, ant, rooms, line);
	else if ((var_valid->stage == 2 || var_valid->stage == 1))
		stage_link(var_valid, line, rooms);
}

void				free_map(t_anthill *ant, char *line)
{
	char *tmp;

	tmp = ant->map;
	ant->map = ft_strjoin_free(ant->map, line, 0, 1);
	free(tmp);
	tmp = ant->map;
	ant->map = ft_strjoin_free(ant->map, ft_strdup("\n"), 0, 1);
	free(tmp);
}

void				stage_rooms_2(t_var_valid *var_valid,
								t_anthill *ant, t_room *rooms, char *line)
{
	if (var_valid->type == 4)
	{
		if (var_valid->start == 1 || var_valid->type_past == 5)
			error("after ##end there cannot be ##start");
		var_valid->type_past = var_valid->type;
		var_valid->start = 1;
		var_valid->n_comm++;
	}
	else if (var_valid->type == 5)
	{
		if (var_valid->end == 1 || var_valid->type_past == 4)
			error("after ##start there cannot be ##end");
		var_valid->type_past = var_valid->type;
		var_valid->end = 1;
		var_valid->n_comm++;
	}
	else if (var_valid->type == 1)
	{
		pars_line_room(ant, rooms, line, var_valid);
		var_valid->type_past = var_valid->type;
	}
}
