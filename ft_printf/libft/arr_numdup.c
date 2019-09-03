/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_numdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:15:33 by emeha             #+#    #+#             */
/*   Updated: 2019/03/28 18:37:55 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*arr_numdup(int *num, int len)
{
	int *num2;
	int i;

	i = 0;
	num2 = NULL;
	if (num != NULL && len != 0)
	{
		num2 = (int*)malloc(sizeof(int) * len);
		while (i < len)
		{
			num2[i] = num[i];
			i++;
		}
	}
	return (num2);
}
