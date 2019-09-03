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

void		validation(t_anthill *ant)
{
	char		*line;
	int			fd;
	t_sys_var	*vars;
	t_room		*rooms;

	vars = (t_sys_var*)malloc(sizeof(t_sys_var));
	vars->n_comm = 0;
	vars->stat = 0;
	rooms = new_room();
	fd = open("/Users/emeha/Desktop/lem_in", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		vars->type = check_line(line);
		if (vars->type == -1 ||
			vars->n_comm > 2 ||
			((vars->type == 4 || vars->type == 6) && vars->type_past == 4) ||
			((vars->type == 5 || vars->type == 6) && vars->type_past == 5) ||
			(vars->stat == 1 && vars->type == 0) ||
			(vars->stat == 0 && ant->rooms > 0))
			error();
		if (vars->type == 4 || vars->type == 5)
		{
			vars->type_past = vars->type;
			vars->n_comm++;
		}
		else
		{
			if ((vars->type_past == 4 || vars->type_past == 5))
			{
				if (vars->type != 1)
					error();
				pars_line(ant, rooms, line, vars->type_past);
				vars->type_past = 0;
			}
			else
			{
				if (vars->type == 0 && vars->stat == 0)
				{
					vars->stat++;
					pars_line(ant, rooms, line, vars->type);
				}
				else
					pars_line(ant, rooms, line, vars->type);
			}
		}
		free(line);
	}
	print_rooms(rooms);
	print_rooms(rooms);
	free_rooms(rooms);
	ft_printf("rooms: %d\n", ant->rooms);
	ft_printf("ants:  %d\n", ant->ants);
}