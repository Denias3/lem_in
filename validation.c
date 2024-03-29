/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 03:17:40 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 18:35:59 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"

t_var_valid			*new_var_valid(void)
{
	t_var_valid		*var_valid;

	var_valid = (t_var_valid*)malloc(sizeof(t_var_valid));
	var_valid->n_comm = 0;
	var_valid->stage = 0;
	var_valid->start = 0;
	var_valid->type = -1;
	var_valid->type_past = -1;
	var_valid->end = 0;
	return (var_valid);
}

void				stage_num_ant(t_var_valid *var_valid,
		t_anthill *ant, char *line)
{
	if (var_valid->type == 4 || var_valid->type == 5)
		error("##start and ##end should be "
		"in front of the room");
	else if (var_valid->type == 0)
	{
		ant->ants = ft_atoi(line);
		var_valid->stage = 1;
	}
	else
		error("at the very beginning should be "
		"the number of ants");
}

void				stage_rooms(t_var_valid *var_valid,
		t_anthill *ant, t_room *rooms, char *line)
{
	if (var_valid->type == 1 || var_valid->type == 4 || var_valid->type == 5)
	{
		if (var_valid->n_comm <= 2)
			stage_rooms_2(var_valid, ant, rooms, line);
		else
			var_valid->stage = 2;
	}
	else
		error("not valid map");
}

void				stage_link(t_var_valid *var_valid,
		char *line, t_room *rooms)
{
	if (var_valid->type == 2)
	{
		var_valid->stage = 2;
		if (pars_line_link(rooms, line) == 1)
			error("not valid link");
	}
	else
		error("not valid map");
}

void				validation(t_anthill *ant, t_room *rooms)
{
	char			*line;
	int				fd;
	t_var_valid		*var_valid;

	var_valid = new_var_valid();
	fd = open("/Users/fschille/Desktop/lem_in/maps/m2", O_RDONLY);
//	fd = 0;
	while (get_next_line(fd, &line) > 0)
	{
		var_valid->type = check_line(line);
		if (var_valid->type == -1)
			error("not valid line in the map");
		if (var_valid->type == 6 || var_valid->type == 3)
		{
			free_map(ant, line);
			continue ;
		}
		validation_2(ant, rooms, var_valid, line);
		free_map(ant, line);
	}
	if (var_valid->stage != 2 || var_valid->n_comm != 2)
		error("all conditions of the card are not met");
	free(var_valid);
}
