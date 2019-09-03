/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_delim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:16:26 by emeha             #+#    #+#             */
/*   Updated: 2019/03/27 17:51:12 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	num_delim(char *str, char c)
{
	int i;
	int s;
	int ch;

	if (str == NULL)
		return (-1);
	i = 0;
	s = 0;
	while (str[i])
	{
		ch = 1;
		while (str[i] != c)
		{
			if (str[i] == '\0')
				return (s);
			if (ch == 1)
			{
				ch = 0;
				s++;
			}
			i++;
		}
		i++;
	}
	return (s);
}
