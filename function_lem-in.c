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
	room->state = 0;
	room->x = -1;
	room->y = -1;
	room->bf = -1;
	room->closed_links = NULL;
	room->visit = 0;
	room->next = NULL;
	room->next_rooms = (t_room**)malloc(sizeof(t_room*) * 2);
	room->next_rooms[0] = NULL;
	room->next_rooms[1] = NULL;
	room->bfs_next = NULL;
	room->bfs_prev = NULL;
	return (room);
}

void	free_rooms(t_room *rooms)
{
	t_room	*tmp;

	while (rooms != NULL)
	{
		if (rooms->closed_links != NULL)
		{
			free(rooms->closed_links);
			rooms->closed_links = NULL;
		}
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
		ft_printf("id:    %d\n", room->id);
		ft_printf("name:  %s", room->name);
		if (room->type == 3)
			ft_printf("_in\n");
		else if (room->type == 4)
			ft_printf("_out\n");
		else
			ft_printf("\n");
		ft_printf("bf:    %d\n", room->bf);
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

void		print_close_links(t_room *room)
{
	int i;

	i = 0;
	ft_printf("\n-------------\n");
	ft_printf("name - %s", room->name);
	if (room->type == 3)
		ft_printf("_in\n");
	else if (room->type == 4)
		ft_printf("_out\n");
	else
		ft_printf("\n");
	ft_printf("Links:\n");
	while (room->next_rooms[i] != NULL)
	{
		ft_printf("%s", room->next_rooms[i]->name);
		if (room->next_rooms[i]->type == 3)
			ft_printf("_in - ");
		else if (room->next_rooms[i]->type == 4)
			ft_printf("_out - ");
		else
			ft_printf(" - ");
		if (room->closed_links == NULL || room->closed_links[i] == 0)
			ft_printf("open(%d)\n", 0);
		else if (room->closed_links[i] == 1)
			ft_printf("close(%d)\n", 1);
		else if (room->closed_links[i] == 2)
			ft_printf("line(%d)\n", 2);
		else if (room->closed_links[i] == 3)
			ft_printf("line(%d)\n", 3);
		i++;
	}
}

void	print_way(t_room *room, int *way)
{
	int i;
	t_room *st_room;

	i = 1;
	st_room = search_room_type(room, 1);
	while (i - 1 <= way[0])
	{

		if (st_room->type == 2)
		{
			ft_printf("%s(%d)", st_room->name, st_room->state);
			break ;
		}
		ft_printf("%s(%d)-", st_room->name, st_room->state);
		st_room = st_room->next_rooms[way[i]];
		i++;
	}
}

void	print_ways(t_room *rooms, t_anthill *ant)
{

	int j;


	j = 0;

	while (ant->ways[j] != NULL)
    {
        print_way(rooms, ant->ways[j]);
        ft_printf("\n");
        j++;
    }
    ft_printf("**-------**\n");
}

void	print_rooms(t_room *rooms, int t)
{
	while (rooms != NULL)
	{
		if (t == 1)
			print_room(rooms);
		else if (t == 0)
			print_close_links(rooms);
		rooms = rooms->next;
	}
	ft_printf("\n\n*************\n*************\n\n");
}

void	error(void)
{
	ft_printf("error\n");
	exit(0);
}