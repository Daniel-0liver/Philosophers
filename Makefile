GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

NAME		=	philo

HEADER		=	./includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/philo.c \
				src/philo_utils.c

CC			=	gcc
FLAGS		=	-pthread -Wall -Wextra -Werror -I${HEADER} -fsanitize=address -o

all:		obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $@ $^

obj:
			@mkdir -p obj

obj/%.o:	src/%.c ./includes/philo.h
			$(CC) $(FLAGS) $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re