/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:39:50 by emeha             #+#    #+#             */
/*   Updated: 2019/04/10 05:32:02 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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

static int	the_room(char *str)
{
	int		i;
	char	**split;

	split = ft_strsplit(str, ' ');
	i = 0;
	if (count_char_double_array(split) != 3)
	{
		free_char_double_array(split);
		return (0);
	}
	while (split[0][i])
	{
		if (split[0][0] == 'L' ||  split[0][0] == '#' ||
			split[0][i] == ' ' || ft_isprint(split[0][i]) == 0)
		{
			free_char_double_array(split);
			return (0);
		}
		i++;
	}
	i = 0;
	if (check_number(split[1]) == 0 || check_number(split[2]) == 0)
	{
		free_char_double_array(split);
		return (0);
	}
	free_char_double_array(split);
	return (1);
}

static int	the_link(char *str)
{
	int i;
	int ch;

	i = 0;
	ch = 0;
	while (i < 2)
	{
		if (*str == 'L' || *str == '#' )
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

static int 	the_comment(char *str)
{
	if (*str == '#')
	{
		str++;
		if (*str != '#')
			return (1);
	}
	return (0);
}

static int 	no_valid_command(char *str)
{
	if (*str == '#')
	{
		str++;
		if (*str == '#')
			return (1);
	}
	return (0);
}

int			check_line(char *line)
{
	if (check_number(line))
		return (0);
	else if (the_room(line))
		return (1);
	else if (the_link(line))
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
