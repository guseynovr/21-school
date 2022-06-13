NAME		=	libftprintf.a

LIBFT_NAME	=	libft.a

DEPS		=	./includes/ft_printf.h	\
				./includes/libft.h

SRCS		=	ft_printf.c				\
				parse.c					\
				print.c					\
				print_int.c				\
				print_hex_unsigned.c	\
				utils.c

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -I./includes

AR			=	ar

ARFLAGS		=	rcs

LIBFT_DIR	=	./libft

LIB_FLAGS	=	-L${LIBFT_DIR} -lft

RM			=	rm -f

%.o:		%.c ${DEPS}  
			$(CC) $(CFLAGS) -c -o $@ $<

${NAME}:	${OBJS}
			@make -C ${LIBFT_DIR}
			${AR} ${ARFLAGS} ${NAME} $? $(wildcard libft/*.o)

all:		${NAME}

clean:
			@make -C ${LIBFT_DIR} clean
			${RM} ${OBJS}

fclean:		clean
			@make -C ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean 
			@make -C ${LIBFT_DIR} re 
			make all

.PHONY:		all clean fclean re
