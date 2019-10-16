/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeha <emeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:41:43 by emeha             #+#    #+#             */
/*   Updated: 2019/06/18 17:02:34 by emeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/time.h>
#include <stdio.h>

int					main(void)
{
	t_anthill		*ant;
	t_room			*rooms;

	struct timeval  tv;
	gettimeofday(&tv, NULL);

	double time_begin = ((double)tv.tv_sec) * 1000 +
						((double)tv.tv_usec) / 1000;

	rooms = new_room();
	ant = newanthill();
	validation(ant, rooms);

	gettimeofday(&tv, NULL);
	double time_end = ((double)tv.tv_sec) * 1000 +
					  ((double)tv.tv_usec) / 1000 ;

	double total_time_ms = time_end - time_begin;

	printf("TOTAL TIME val (ms) = %f\n", total_time_ms);

	gettimeofday(&tv, NULL);

	time_begin = ((double)tv.tv_sec) * 1000 +
						((double)tv.tv_usec) / 1000;
	algorithm(ant, rooms);
	free_track_record(ant);
	free_rooms(rooms);
	gettimeofday(&tv, NULL);
	time_end = ((double)tv.tv_sec) * 1000 +
					  ((double)tv.tv_usec) / 1000 ;

	total_time_ms = time_end - time_begin;
	printf("TOTAL TIME alg (ms) = %f\n", total_time_ms);
	return (0);
}
