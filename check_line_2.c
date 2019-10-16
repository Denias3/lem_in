/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:26:42 by emeha             #+#    #+#             */
/*   Updated: 2019/10/10 17:26:44 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			the_room(char *str, int i)
{
	char	**split;

	split = ft_strsplit(str, ' ');
	if (count_char_double_array(split) != 3)
	{
		free_char_double_array(split);
		return (0);
	}
	while (split[0][i])
	{
		if (split[0][0] == 'L' || split[0][0] == '#' ||
			split[0][i] == ' ' || ft_isprint(split[0][i]) == 0)
		{
			free_char_double_array(split);
			return (0);
		}
		i++;
	}
	if (check_number(split[1]) == 0 || check_number(split[2]) == 0)
	{
		free_char_double_array(split);
		return (0);
	}
	free_char_double_array(split);
	return (1);
}

int			the_link(char *str, int i, int ch)
{
	while (i < 2)
	{
		if (*str == 'L' || *str == '#')
			return (0);
		while (*str)
		{
			if (ch)
				ch = 2;
			if (*str == '-')
			{
				ch = 1;
				str++;
				break ;
			}
			if (*str == ' ' || ft_isprint(*str) == 0)
				return (0);
			str++;
		}
		i++;
	}
	if (ch == 2)
		return (1);
	return (0);
}
