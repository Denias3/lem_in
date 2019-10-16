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
			if (ent[ft_strlen(name_room)] == '-')
			{
				links_room[j] = (char*)malloc(sizeof(char) * ft_strlen(links[i]));
				ft_strcpy(links_room[j], (ent + ft_strlen(name_room) + 1));
				j++;
			}
			else if (ent[ft_strlen(name_room)] == '\0')
			{
				links_room[j] = (char*)malloc(sizeof(char) * ft_strlen(links[i]));
				ft_strncpy(links_room[j], links[i], search_char(links[i], '-'));
				j++;
			}
		}
		i++;
	}
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
		if (ft_strcmp(links_room[j], room->name) == 0)
		{
			rooms->next_rooms[i] = room;
			return ;
		}
		j++;
	}
}

int 		linking(t_room *rooms, t_anthill *ant)
{
	t_room	*room;
	char 	**links_room;

	while (rooms != NULL)
	{
		links_room = links_for_room(rooms->name, ant->links);
		rooms->next_rooms = (t_room**)malloc(sizeof(t_room*) * (size_arr(links_room) + 1));
		room->next_rooms[0] = NULL;
		room = rooms->next;
		while (room != NULL)
		{
			write_next_rooms(rooms, room, links_room)
			room = room->next;
		}
		rooms = rooms->next;
	}
}