GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

NAME		=	philo

HEADER		=	./includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))
SRC			=	src/philo.c \
				src/philo_utils.c\
				src/philo_routine.c\
				src/philo_check_args.c \
				src/philo_thread_init.c

CC			=	gcc
FLAGS		=	-pthread -I${HEADER} -Wall -Wextra -Werror -g -fsanitize=leak

all:		obj $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^

obj:
			@mkdir -p obj

obj/%.o:	src/%.c ./includes/philo.h
			@$(CC) $(FLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

valgrind:	all
	valgrind --leak-check=full --show-leak-kinds=all --quiet ./philo 10 10 300 4 5

hellgrind:	all
	valgrind --quiet --tool=helgrind ./philo 10 10 300 400

clean:
			@rm -rf $(OBJ) obj
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re