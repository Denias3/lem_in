/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:42:09 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 17:44:08 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf/ft_printf.h"

typedef	struct		s_room
{
	char			*name;
	int				id;
	short			type; // 0 - обычная комната, 1 -  start, 2 - end
	short			state; // 0 - нет муравья, 1 - есть муравей
	int				x;
	int				y;
	struct s_room	**next_rooms;
	struct s_room	*next;

}					t_room;

typedef	struct		s_anthill
{
	int				ants;
	int				rooms;
	int				max_x;
	int				max_y;
}					t_anthill;

/*
**			s_sys_var
**		type_past	-   прошлый тип линии
**		type		- 	тип линии
**		stat		-
**		n_comm		-	количество комманд
*/

typedef struct		s_sys_var
{
	// validation

	int				type_past;
	int				type;
	int 			stat;
	int				n_comm;

}					t_sys_var;

int					check_line(char *line);
int					count_char_double_array(char **str);
void				free_char_double_array(char **str);
void				validation(t_anthill *ant, t_room *rooms);
int					pars_line(t_anthill *ant, t_room *room, char *line, int type);
void				print_rooms(t_room *rooms);
t_room				*new_room(void);
void				free_rooms(t_room *rooms);
void				error(void);

#endif
