GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

NAME		=	philo

HEADER		=	./includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/philo.c \
				src/philo_check_args.c \
				src/philo_thread_init.c \
				src/philo_utils.c

CC			=	gcc
FLAGS		=	-pthread -I${HEADER} -Wall -Wextra -Werror #-fsanitize=address

all:		obj $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^

obj:
			@mkdir -p obj

obj/%.o:	src/%.c ./includes/philo.h
			@$(CC) $(FLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

valgrind:	all
	valgrind --leak-check=full --show-leak-kinds=all --quiet ./philo 10 1 1 4 5

hellgrind:	all
	valgrind --quiet --tool=helgrind ./philo 10 100 1 400 50

clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re