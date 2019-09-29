/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lem-in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:02:06 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 17:56:09 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		count_char_double_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_char_double_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_room	*new_room(void)
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room->name = NULL;
	room->id = -1;
	room->type = -1;
	room->state = -1;
	room->x = -1;
	room->y = -1;
	room->bf = -1;
	room->next = NULL;
	room->next_rooms = (t_room**)malloc(sizeof(t_room*) * 2);
	room->next_rooms[0] = NULL;
	room->next_rooms[1] = NULL;
	return (room);
}

void	free_rooms(t_room *rooms)
{
	t_room	*tmp;

	while (rooms != NULL)
	{
		free(rooms->next_rooms);
		free(rooms->name);
		tmp = rooms;
		rooms = rooms->next;
		free(tmp);
	}
}

void	print_room(t_room *room)
{
	if (room != NULL)
	{
		ft_printf("name:  %s\n", room->name);
		ft_printf("type:  %d\n", room->type);
		ft_printf("state: %d\n", room->state);
		ft_printf("x:     %d\n", room->x);
		ft_printf("y:     %d\n\n", room->y);
	}
	else
	{
		ft_printf("NULL");
	}
}

void	print_rooms(t_room *rooms)
{
	int i;
	i = 0;
	while (rooms != NULL)
	{
		ft_printf("id:    %d\n", i);
		print_room(rooms);
		i++;
		rooms = rooms->next;
	}
}

void	error(void)
{
	ft_printf("error\n");
	exit(0);
}