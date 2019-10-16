/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_acc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:34:47 by emeha             #+#    #+#             */
/*   Updated: 2019/10/07 18:34:52 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cop_ways_acc(int *ways_acc, int *ways_acc_tmp,  int size)
{
	while (--size >= 0)
		ways_acc[size] = ways_acc_tmp[size];
}

int		iteration_ways_acc(int *ways_acc, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (ways_acc[i] == 0)
		{
			ways_acc[i] = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
