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



void        stage_num_ant(t_var_valid *var_valid, t_anthill *ant, char *line)
{
    if (var_valid->type == 4 || var_valid->type == 5 ||
        var_valid->type == 6 || var_valid->type == -1)
        error();
    else if (var_valid->type == 0)
    {
        ant->ants = ft_atoi(line);
        var_valid->stage = 1;
    }
}

void        stage_rooms(t_var_valid *var_valid, t_anthill *ant, t_room *rooms, char *line)
{
    if (var_valid->type == 6 || var_valid->type == -1)
        error();
    else if (var_valid->type == 1 || var_valid->type == 4 || var_valid->type == 5)
    {
        pars_line(ant, rooms, line, var_valid->type);
        var_valid->stage = 1;
    }
}

void		validation(t_anthill *ant, t_room *rooms)
{
	char		*line;
	int			fd;
    t_var_valid	*var_valid;


	var_valid = (t_var_valid*)malloc(sizeof(t_var_valid));
    var_valid->n_comm = 0;
    var_valid->stage = 0;

	fd = open("C:\\Users\\balak\\CLionProjects\\lem_in\\text", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
        var_valid->type = check_line(line);
        if (var_valid->stage == 0 && var_valid->type != 3)
            stage_num_ant(var_valid, ant, line);
        if (var_valid->stage == 1 && var_valid->type != 3)
            stage_rooms(var_valid, ant, rooms, line);

		free(line);
	}
	print_rooms(rooms);
	free_rooms(rooms);
//	ft_printf("rooms: %d\n", ant->rooms);
//	ft_printf("ants:  %d\n", ant->ants);
}