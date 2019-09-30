/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 01:18:18 by fschille          #+#    #+#             */
/*   Updated: 2019/09/30 01:18:23 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
​
#include "lem-in.h"
​
void		ft_tmp(t_room *rooms)
{
	rooms->bf = 0;
	rooms = rooms->next_rooms[0];
	rooms->bf = 1;
	rooms = rooms->next_rooms[1];
	rooms->bf = 2;
	rooms = rooms->next_rooms[1];
	rooms->bf = 2;
	rooms = rooms->next_rooms[1];
	rooms->bf = 3;
	rooms = rooms->next_rooms[1];
	rooms->bf = 3;
	rooms = rooms->next_rooms[0];
	rooms->bf = 2;
	rooms = rooms->next_rooms[1];
	rooms->bf = 1;
}
​
t_room		*end_room(t_room *rooms)
{
	while (rooms != NULL)
	{
		if (rooms->type == 2)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}
​
int 		size_link(t_room *rooms)
{
	int		size;
	​
	size = 0;
	while (rooms->next_rooms[size] != NULL)
		size++;
	return (size);
}
​
int 		*creat_closed_links(int size)
{
	int 	*closed_links;
	int		i;
	​
	i = 0;
	closed_links = (int*)malloc(sizeof(int) * size);
	while(i < size)
	{
		closed_links[i] = 0;
		i++;
	}
	return (closed_links);
}
​
void		close_link(t_room *room, t_room *tmp)
{
	​
}
​
int			df_check(t_room *rooms)
{
	t_room	*tmp;
	int		i;
	​
	​
	tmp = NULL;
	i = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		if (rooms->bf == rooms->next_rooms[i]->bf && tmp == NULL)
			tmp = rooms->next_rooms[i];
		if (rooms->bf == rooms->next_rooms[i]->bf + 1)
			tmp = rooms->next_rooms[i];
		i++;
	}
	tmp->closed_links = creat_closed_links(size_link(tmp));
	close_link(room, t_room *tmp);
}
​
void		short_way(t_room *rooms)
{
	ft_tmp(rooms);
	rooms = end_room(rooms);
	if (rooms == NULL)
	{
		ft_printf("error finding (end) room");
		exit(0);
	}
//	ft_printf("%s - room\n", tmp->name);
//	ft_printf("%d - bf\n", tmp->bf);
//	ft_printf("%d - type\n", tmp->type);
}