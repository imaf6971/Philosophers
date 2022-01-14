NAME	=	philo

HEADER	=	phils.h

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I $(HEADER)

SRCS	=	main.c ft_atoul.c philosopher.c sleep_and_eat.c fork_operations.c time_utils.c thread_utils.c logger.c
OBJ		=	$(patsubst %.c, %.o, $(SRCS))

.PHONY	:	all	clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	$(CC) $(CFLAGS)	$(OBJ) -o $(NAME)

%.o		:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	rm -f $(OBJ)

fclean	:
	rm -f $(NAME) $(OBJ)

re		: fclean all