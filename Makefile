NAME = lem-in

SRC = lem-in.c\
check_line.c\
function_lem-in.c\
validation.c\
pars_line.c\
algorithm.c

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