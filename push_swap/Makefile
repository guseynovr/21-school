NAME	=	push_swap

B_NAME	=	checker

HEADERS	=	push_swap.h quicksort.h operations.h content.h	\
			get_next_line.h

HDIR	=	include

LIBFT	=	libft/libft.a

SRCS	=	main.c sort.c validation.c operations.c	\
			content_getters.c content_setters.c		\
			init_stack.c quicksort.c find.c array.c	\
			sort_utils.c

B_SRCS	=	checker.c init_stack.c validation.c		\
			content_getters.c content_setters.c		\
			sort_utils.c operations.c				\
			get_next_line.c get_next_line_utils.c

SRCSDIR	=	src

OBJS	=	$(addprefix $(SRCSDIR)/, $(SRCS:.c=.o))

B_OBJS	=	$(addprefix $(SRCSDIR)/, $(B_SRCS:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I./libft -I./$(HDIR)

LFLAGS	=	-L./libft -lft

RM		=	rm -f

%.o:		%.c $(addprefix $(HDIR)/, $(HEADERS))
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

bonus:		checker

checker:	$(B_OBJS) $(LIBFT)
			$(CC) $(B_OBJS) $(LFLAGS) -o $(B_NAME)

$(LIBFT):	
			@make -s -C libft
			@make bonus -s -C libft

clean:		
			@make clean -s -C libft
			@$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
			@make fclean -s -C libft
			@$(RM) $(NAME) $(B_NAME)

re:			fclean all

.PHONY	=	all clean fclean re checker
