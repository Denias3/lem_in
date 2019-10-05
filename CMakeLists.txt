cmake_minimum_required(VERSION 3.13)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Werror -Wextra")
file(GLOB LIBFT ft_printf/*.c ft_printf/*.h ft_printf/libft/*.c ft_printf/libft/*.h)
set(SOURCES  lem-in.c
        check_line.c
        function_lem-in.c
        validation.c
        pars_line.c
        algorithm.c short_way.c go_ants.c track_record.c room_sharing.c join_room.c)


add_executable(lem_in ${SOURCES} ${LIBFT})