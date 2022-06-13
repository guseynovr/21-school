NAME		=	libft.a

HEADERS		=	libft.h

SRCS		=	ft_memset.c		ft_strlen.c		ft_isalpha.c	ft_strdup.c		\
				ft_bzero.c		ft_strlcpy.c	ft_isdigit.c	ft_substr.c		\
				ft_memcpy.c		ft_strlcat.c	ft_isalnum.c	ft_strjoin.c	\
				ft_memccpy.c	ft_strchr.c		ft_isascii.c	ft_strtrim.c	\
				ft_memmove.c	ft_strrchr.c	ft_isprint.c	ft_split.c		\
				ft_memchr.c		ft_strnstr.c	ft_toupper.c	ft_strmapi.c	\
				ft_memcmp.c		ft_strncmp.c	ft_tolower.c	ft_itoa.c		\
				ft_putchar_fd.c	ft_strcmp.c										\
				ft_putstr_fd.c	ft_atoi.c										\
				ft_putendl_fd.c	ft_atol.c										\
				ft_putnbr_fd.c  ft_calloc.c	

SRCSBONUS	=	ft_lstnew.c			ft_lstdelone.c	\
				ft_lstadd_front.c	ft_lstclear.c	\
				ft_lstsize.c		ft_lstiter.c	\
				ft_lstlast.c		ft_lstmap.c		\
				ft_lstadd_back.c

OBJS		=	${SRCS:.c=.o}

OBJSBONUS	=	${SRCSBONUS:.c=.o}

AR			=	ar

ARFLAGS		=	rsc

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

%.o:			%.c ${HEADERS}
				$(CC) $(CFLAGS) -c -o $@ $<

${NAME}:		${OBJS}
				${AR} ${ARFLAGS} ${NAME} $?

bonus:			${OBJSBONUS}
				${AR} ${ARFLAGS} ${NAME} $?

all:			${NAME}

clean:			
				${RM} ${OBJS} ${OBJSBONUS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all re clean fclean
