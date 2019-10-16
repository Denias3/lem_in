cmake_minimum_required(VERSION 3.13)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Werror -Wextra")
file(GLOB LIBFT ft_printf/*.c ft_printf/*.h ft_printf/libft/*.c ft_printf/libft/*.h)
set(SOURCES lem_in.c
        check_line.c
        function_lem_in.c
        validation.c
        pars_line.c
        algorithm.c short_way.c go_ants.c track_record.c room_sharing.c join_room.c to_position.c ways_acc.c right_ways.c pars_line_2.c function_lem_in_2.c check_line_2.c validation_2.c algorithm_2.c algorithm_3.c)


add_executable(lem_in ${SOURCES} ${LIBFT})