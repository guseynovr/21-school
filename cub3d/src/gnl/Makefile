ROOT_DIR	= ../../

NAME		= $(ROOT_DIR)libgnl.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

INCLUDE_DIR	= $(ROOT_DIR)inc

HEADER		= $(INCLUDE_DIR)/get_next_line.h

AR 			= ar rcs

OBJ_DIR		= $(ROOT_DIR)objects/gnl/

SRC			=	get_next_line.c			\
				get_next_line_utils.c

OBJS		=	$(addprefix $(OBJ_DIR), $(SRC:c=o))


RM			=	rm -f

$(OBJ_DIR)%.o:		%.c $(HEADER)
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)


$(NAME):			$(OBJS)
					@$(AR) $@ $?

all:				$(NAME)

clean:
						@$(RM) $(OBJS)

fclean: 				clean
						@$(RM) $(NAME)

re: 					clean all

.PHONY: 				all clean fclean re