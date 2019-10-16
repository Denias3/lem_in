/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 05:41:40 by fschille          #+#    #+#             */
/*   Updated: 2019/10/16 05:41:42 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 		size_arr(char **arr)
{
	int 	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int 		search_char(char *str, char elem)
{
	int 	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == elem)
			return (i);
		i++;
	}
	return (-1);
}

char 		**links_for_room(char *name_room, char **links)
{
	int 	i;
	int 	j;
	char 	**links_room;
	char 	*ent;

	i = 0;
	j = 0;
	links_room = (char**)malloc(sizeof(char*) * size_arr(links));
	while (links[i] != NULL)
	{
		if ((ent = ft_strstr(links[i], name_room)) != NULL)
		{
			if (ent[ft_strlen(name_room)] == '-' && ft_strncmp(links[i], ent, search_char(links[i], '-')) == 0)
			{
				links_room[j] = (char*)malloc(sizeof(char) * ft_strlen(links[i]));
				ft_strcpy(links_room[j], (ent + ft_strlen(name_room) + 1));
				j++;
			}
			else if (ent[ft_strlen(name_room)] == '\0' && ft_strcmp(links[i] + search_char(links[i], '-') + 1, name_room) == 0)
			{
				links_room[j] = (char*)malloc(sizeof(char) * ft_strlen(links[i]));
				ft_strncpy(links_room[j], links[i], search_char(links[i], '-'));
				j++;
			}
		}
		i++;
	}

	links_room[j] = NULL;
	return (links_room);
}

void		write_next_rooms(t_room *rooms, t_room *room, char **links_room)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (rooms->next_rooms[i] != NULL)
	{
		i++;
	}
	while (links_room[j] != NULL)
	{
		if (links_room[j] != NULL && ft_strcmp(links_room[j], room->name) == 0)
		{
			rooms->next_rooms[i] = room;
			rooms->next_rooms[i + 1] = NULL;
			return ;
		}
		j++;
	}
}

int 		linking(t_room *rooms, t_anthill *ant)
{
	t_room	*room;
	t_room	*st_rooom;
	char 	**links_room;

	st_rooom = rooms;
	while (rooms != NULL)
	{
		links_room = links_for_room(rooms->name, ant->map_links);
		rooms->next_rooms = (t_room**)malloc(sizeof(t_room*) * (size_arr(links_room) + 1));
		rooms->next_rooms[0] = NULL;
		room = st_rooom;
		while (room != NULL)
		{
			if (ft_strcmp(rooms->name, room->name) != 0)
				write_next_rooms(rooms, room, links_room);
			room = room->next;
		}
		rooms = rooms->next;
	}
	return (1);
}