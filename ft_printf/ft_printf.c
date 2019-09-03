/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:42:56 by emeha             #+#    #+#             */
/*   Updated: 2019/03/27 16:55:39 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int g_s;

int					ft_printf(char *format, ...)
{
	va_list ap;

	g_s = 0;
	va_start(ap, format);
	solve_printf(format, ap);
	va_end(ap);
	return (g_s);
}
