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
	short			type;
	int				state;
	int				x;
	int				y;
	int				bf;
	int				visit;
	int				*closed_links;
	struct s_room	**next_rooms;
	struct s_room	*next;
	struct s_room	*bfs_next;
	struct s_room	*bfs_prev;
}					t_room;

typedef	struct		s_anthill
{
	int				ants;
	char			*map;
	t_room			*end_room;
	int				rooms;
	int				*shortest_way;
	int				*r_shortest_way;
	int				**ways;
	int				**r_ways;
}					t_anthill;

/*
**			s_var_valid
**		type_past	-   прошлый тип линии
**		type		- 	тип линии
**		stage		-   этап
**		  0   -   Количество муравьев
**		  1   -   Создание комнат
**		  2   -   Линковка комнат
**		n_comm		-	количество комманд
*/

typedef struct		s_var_valid
{
	int				start;
	int				end;
	int				type;
	int				type_past;
	int				stage;
	int				n_comm;

}					t_var_valid;

t_anthill			*newanthill(void);
int					check_line(char *line);
int					count_char_double_array(char **str);
void				free_char_double_array(char **str);
void				validation(t_anthill *ant, t_room *rooms);
int					pars_line_room(t_anthill *ant, t_room *room, char *line,
		t_var_valid *v_val);
t_room				*check_name(t_room *rooms, char *name, char *name_link);
t_room				*new_room(void);
void				free_rooms(t_room *rooms);
void				error(char *text);
int					pars_line_link(t_room *room, char *line);
void				algorithm(t_anthill *ant, t_room *rooms);
t_room				*search_room_type(t_room *rooms, short type);
int					short_way(t_room *rooms, t_anthill *ant, int i);
void				go_ants(t_room *rooms, t_anthill *ant, int *ways_acc, int j);
void				rooms_sharing(t_room *room_in, t_anthill *ant);
void				track_record(int *way, t_anthill *ant);
void				free_track_record(t_anthill *ant);
t_room				*end_rooms(t_room *rooms);
int					size_link(t_room *room);
void				redirect_link(t_room *room, t_room *new_room, char *name);
void				del_copies(t_room *rooms, t_anthill *ant, int i, int red);
void				free_ways(t_anthill *ant);
int					*creat_closed_links(int size);
int					len_int(int **way);
int					*my_intrevers(int *way);
int					iteration_ways_acc(int *ways_acc, int size);
void				go_way(t_room *end_rooms, int *way);
int					*right_ways(t_anthill *ant, int count, int tmp_count);
void				cop_ways_acc(int *ways_acc, int *ways_acc_tmp, int size);
void				memolloc_room(t_room *room1, t_room *room2, int i);
int					the_room(char *str, int i);
int					the_link(char *str, int i, int ch);
t_room				*search_start_room(t_room *rooms);
int					to_position_2(t_room *rooms);
int					check_num(char *num);
void				free_map(t_anthill *ant, char **line);
t_room				*end_room_next(t_room *rooms);
int					ended_way(t_room *room);
int					possible_ways(t_room *room);
int					delet_xlink(t_room *room, int id);
void				search_xlink(t_room *room, t_anthill *ant);
int					check_xlink(t_room *room, t_anthill *ant);
void				null_visit_close(t_room *rooms);
void				all_creat_closed_links(t_room *rooms);

#endif
