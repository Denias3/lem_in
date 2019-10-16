/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 06:26:57 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 06:26:59 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				map_rooms_size(t_anthill *ant)
{
	int i;

	i = 0;
	while(ant->map_rooms[i] != NULL)
		i++;
	return (i);
}

void			memaloc_map_rooms(t_anthill *ant, char *name)
{
	int		i;
	int		size;
	char	**tmp_nap_rooms;

	i = 0;
	if (ant->map_rooms == NULL)
	{
		ant->map_rooms = (char**)malloc(sizeof(char*) * 2);
		ant->map_rooms[0] = ft_strdup(name);
		ant->map_rooms[1] = NULL;
	}
	else
	{
		size = map_rooms_size(ant);
		tmp_nap_rooms = (char**)malloc(sizeof(char*) * (size + 2));
		while (ant->map_rooms[i] != NULL)
		{
			tmp_nap_rooms[i] = ant->map_rooms[i];
			i++;
		}
		tmp_nap_rooms[i] = ft_strdup(name);
		tmp_nap_rooms[i + 1] = NULL;
		free(ant->map_rooms);
		ant->map_rooms = tmp_nap_rooms;
	}
}
