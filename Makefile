GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

NAME		=	philo

HEADER		=	./includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/philo.c \
				src/philo_utils.c

CC			=	gcc
FLAGS		=	-pthread -Wall -Wextra -Werror -I${HEADER} -fsanitize=address

all:		obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $@ $^

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			@echo "$@ $(GREEN)created$(RESET)"
			$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re