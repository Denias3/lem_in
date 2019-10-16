/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:18:23 by emeha             #+#    #+#             */
/*   Updated: 2019/10/16 11:18:24 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//void				validation_2(t_anthill *ant, t_room *rooms)
//{
//
//}

void				free_map(t_anthill *ant, char **line)
{
	char *tmp;

	tmp = ant->map;
	ant->map = ft_strjoin_free(ant->map, (*line), 0, 1);
	free(tmp);
	tmp = ant->map;
	ant->map = ft_strjoin_free(ant->map, ft_strdup("\n"), 0, 1);
	free(tmp);
}