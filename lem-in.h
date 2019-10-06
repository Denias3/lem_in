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
							// 3 - room_in, 4 - room_out
	short			state; // 0 - нет муравья, 1 - есть муравей
	int				x;
	int				y;
	int             bf;
	int             visit;
	int 			*closed_links;
	struct s_room	**next_rooms;
	struct s_room	*next;
	struct s_room	*bfs_next;
	struct s_room	*bfs_prev;

}					t_room;

typedef	struct		s_anthill
{
	int				ants;
	int				rooms;
	int 			**ways;
	int				max_x;
	int				max_y;
}					t_anthill;

/*
**			s_var_valid
**		type_past	-   прошлый тип линии
**		type		- 	тип линии
**		stage		-   этап
**          0   -   Количество муравьев
**          1   -   Создание комнат
**          2   -   Линковка комнат
**		n_comm		-	количество комманд
*/

typedef struct		s_var_valid
{
	int             start;
	int             end;
	int				type;
	int             type_past;
	int 			stage;
	int				n_comm;

}					t_var_valid;

int					check_line(char *line);
int					count_char_double_array(char **str);
void				free_char_double_array(char **str);
void				validation(t_anthill *ant, t_room *rooms);
int					pars_line_room(t_anthill *ant, t_room *room, char *line, t_var_valid *v_val);
void				print_room(t_room *room);
void				print_rooms(t_room *rooms, int t);
t_room				*check_name(t_room *rooms, char *name);
t_room				*new_room(void);
void				free_rooms(t_room *rooms);
void				error(void);
int					pars_line_link(t_room *room, char *line);
void				algorithm(t_anthill *ant, t_room *rooms);
t_room          	*search_room_type(t_room *rooms, short type);
int 			    short_way(t_room *rooms, t_anthill *ant);
void				check_link_room_full(t_room *room);
void				go_ants(t_room *rooms, t_anthill *ant);
void				rooms_sharing(t_room *room_in, t_anthill *ant);
void                track_record(int *way, t_anthill *ant);
void                free_track_record(t_anthill *ant);
void				print_vay(t_room *room, t_anthill *ant);
t_room		        *end_room(t_room *rooms);
int 		        size_link(t_room *room);
void				redirect_link(t_room *room, t_room *new_room, char *name);
void				print_close_links(t_room *room);
void				del_copies(t_room *rooms, t_anthill *ant);
void                null_track_record(t_anthill *ant);
int 		        *creat_closed_links(int size);

#endif
