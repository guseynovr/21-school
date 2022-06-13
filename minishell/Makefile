NAME		=	minishell

SRC			=	main.c tokens.c assemble.c error.c redirect.c exec.c signals.c\
				parse_env.c pwd.c echo.c cd.c export.c unset.c env.c exit.c	\
				expand.c expand_word.c expand_quotes.c utils2.c assemble_utils.c\
				expand_word_heredoc.c exec_utils.c utils.c shlvl.c assemble2.c	\
				error2.c parse_env_utils.c clr_exp.c expand_var.c expand_utils.c \
				expand_quotes_utils.c redirect_utils.c signals2.c
SDIR		=	src

HEADERS		=	minishell.h msh_signal.h
HDIR		=	inc

FTNAME		=	libft.a
FTDIR		=	libft
LIBFT		=	$(FTDIR)/$(FTNAME)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
INC			=	-I$(HDIR) -I$(FTDIR) -I${HOME}/.brew/opt/readline/include
LFLAGS		=	-lreadline -lft -L$(FTDIR) -L${HOME}/.brew/opt/readline/lib

OBJ			=	$(addprefix $(SDIR)/, $(SRC:.c=.o))

RM			=	rm -f

%.o:		%.c $(addprefix $(HDIR)/, $(HEADERS))
			$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(LFLAGS) $(OBJ) -o $@

all:		$(NAME)

$(LIBFT):	
			make -C $(FTDIR)
			make bonus -C $(FTDIR)

clean:		
			make clean -C $(FTDIR)
			$(RM) $(OBJ)

fclean:		clean
			make fclean -C $(FTDIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
