NAME	=	philo_bonus

HEADER	=	bphils.h

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I $(HEADER)

SRCS	=	main.c args.c philosopher.c
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