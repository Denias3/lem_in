NAME = libftprintf.a
FILEC = *.c ./libft/*.c

FILEO = *.o

LIB = ft_printf.h ./libft/libft.h ./libft/get_next_line.h 

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FILEC)
	@gcc $(FLAG) -c $(FILEC) -I $(LIB)
	@ar rc $(NAME) $(FILEO)
	@ranlib $(NAME)
	@echo "compil libftprintf"

clean:
	@rm -rf $(FILEO)
	@echo "clean libftprintf"

fclean: clean
	@rm -rf $(NAME)
	@echo "fclean libftprintf"

re: fclean all
	@echo "re libftprintf"
