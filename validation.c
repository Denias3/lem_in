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
#include "lem-in.h"

t_var_valid *new_var_valid(void)
{
	t_var_valid	*var_valid;

	var_valid = (t_var_valid*)malloc(sizeof(t_var_valid));
	var_valid->n_comm = 0;
	var_valid->stage = 0;
	var_valid->start = 0;
	var_valid->type = -1;
	var_valid->type_past = -1;
	var_valid->end = 0;
	return (var_valid);
}

void        stage_num_ant(t_var_valid *var_valid, t_anthill *ant, char *line)
{
	if (var_valid->type == 4 || var_valid->type == 5)
		error();
	else if (var_valid->type == 0)
	{
		ant->ants = ft_atoi(line);
		var_valid->stage = 1;
	}
	else
		error();
}

void        stage_rooms(t_var_valid *var_valid, t_anthill *ant, t_room *rooms, char *line)
{
	if (var_valid->type == 1 || var_valid->type == 4 || var_valid->type == 5)
	{
		if (var_valid->n_comm <= 2)
		{
			if (var_valid->type == 4)
			{
				if (var_valid->start == 1 || var_valid->type_past == 5)
					error();
				var_valid->type_past = var_valid->type;
				var_valid->start = 1;
				var_valid->n_comm++;
			}
			else if (var_valid->type == 5)
			{
				if (var_valid->end == 1 || var_valid->type_past == 4)
					error();
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
		else
			var_valid->stage = 2;
	}
	else
		error();
}

void        stage_link(t_var_valid *var_valid, t_room *rooms, char *line)
{
	if (var_valid->type == 2)
	{
		var_valid->stage = 2;
		if (pars_line_link(rooms, line) == 1)
			error();
	}
	else
		error();
}

void		validation(t_anthill *ant, t_room *rooms)
{
	char		*line;
	int			fd;
	t_var_valid	*var_valid;

	var_valid = new_var_valid();
	fd = open("/Users/emeha/CLionProjects/lem_in/ex1", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		var_valid->type = check_line(line);
		if (var_valid->type == -1)
			error();
		if (var_valid->type == 6 || var_valid->type == 3)
        {
            free(line);
            continue;
        }
		if (var_valid->stage == 0)
			stage_num_ant(var_valid, ant, line);
		else if (var_valid->stage == 1 && var_valid->type != 2)
			stage_rooms(var_valid, ant, rooms, line);
		else if ((var_valid->stage == 2 || var_valid->stage == 1))
			stage_link(var_valid, rooms, line);
		free(line);
	}
	if (var_valid->stage != 2 || var_valid->n_comm != 2)
		error();
//	print_rooms(rooms);
	free(var_valid);
//	ft_printf("rooms: %d\n", ant->rooms);
//	ft_printf("ants:  %d\n", ant->ants);
}