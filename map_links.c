/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 06:43:08 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 06:43:09 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//int				map_links_size(t_anthill *ant)
//{
//	int i;
//
//	i = 0;
//	while(ant->map_links[i] != NULL)
//		i++;
//	return (i);
//}
//
//void			memaloc_map_links(t_anthill *ant, char *line)
//{
//	int		i;
//	int		size;
//	char	**tmp_nap_links;
//
//	i = 0;
//	if (ant->map_links == NULL)
//	{
//		ant->map_links = (char**)malloc(sizeof(char*) * 2);
//		ant->map_links[0] = ft_strdup(line);
//		ant->map_links[1] = NULL;
//	}
//	else
//	{
//		size = map_links_size(ant);
//		tmp_nap_links = (char**)malloc(sizeof(char*) * (size + 2));
//		while (ant->map_links[i] != NULL)
//		{
//			tmp_nap_links[i] = ant->map_links[i];
//			i++;
//		}
//		tmp_nap_links[i] = ft_strdup(line);
//		tmp_nap_links[i + 1] = NULL;
//		free(ant->map_links);
//		ant->map_links = tmp_nap_links;
//	}
//}
