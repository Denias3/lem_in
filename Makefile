NAME = lem-in

SRC = lem_in.c\
check_line.c\
check_line_2.c\
function_lem_in.c\
function_lem_in_2.c\
validation.c\
pars_line.c\
pars_line_2.c\
algorithm.c\
short_way.c\
go_ants.c\
track_record.c\
room_sharing.c\
join_room.c\
to_position.c\
ways_acc.c\
right_ways.c\
validation_2.c


INCLUDES = ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(SRC)
		@make -C ft_printf
		@gcc -Wall -Werror -Wextra -g $(SRC) $(INCLUDES) -o $(NAME)
		@echo "-> compil lem-in"

comp:
		@gcc -Wall -Werror -Wextra -g $(SRC) $(INCLUDES) -o $(NAME)
		@echo "-> comp lem-in"

clean:
		@make clean -C ft_printf
		@echo "-> clean lem-in"
fclean: clean
		@make fclean -C ft_printf
		@rm -f $(NAME)
		@echo "-> fclean lem-in"

re: fclean all
		@echo "-> re lem-in"