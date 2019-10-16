/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:53:21 by fschille          #+#    #+#             */
/*   Updated: 2019/10/16 11:53:28 by fschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**			check_line
**		return:
**			error          - -1
**			number_of_ants - 0
**			the_room       - 1
**			the_link       - 2
**			comment        - 3
**			command:
**				##start    - 4
**				##end      - 5
**				no valid   - 6
*/

static int		the_comment(char *str)
{
	if (*str == '#')
	{
		str++;
		if (*str != '#')
			return (1);
	}
	return (0);
}

static int		no_valid_command(char *str)
{
	if (*str == '#')
	{
		str++;
		if (*str == '#')
			return (1);
	}
	return (0);
}

int				check_number_positive(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

int				check_line(char *line)
{
	if (check_number_positive(line))
		return (0);
	else if (the_room(line, 0))
		return (1);
	else if (the_link(line, 0, 0))
		return (2);
	else if (the_comment(line))
		return (3);
	else if (ft_strcmp(line, "##start") == 0)
		return (4);
	else if (ft_strcmp(line, "##end") == 0)
		return (5);
	else if (no_valid_command(line) == 1)
		return (6);
	else
		return (-1);
}
