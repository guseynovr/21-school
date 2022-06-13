NAME	=	philo

SRC		=	main.c routine.c init.c utils.c philos.c

SDIR	=	src

HEADERS	=	philo.h

HDIR	=	inc

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INC		=	-I$(HDIR)

OBJ		=	$(addprefix $(SDIR)/, $(SRC:.c=.o))

RM		=	rm -f

%.o:		%.c $(addprefix $(HDIR)/, $(HEADERS))
			$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $@

all:		$(NAME)

clean:		
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
