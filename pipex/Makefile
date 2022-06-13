NAME	=	pipex

SRC		=	main.c $(SRC_C) 

SRC_B	=	main_bonus.c $(SRC_C) 

SRC_C	=	utils_common.c utils_common2.c $(SRC_GNL)

SRC_GNL	=	get_next_line.c get_next_line_utils.c

HEADER	=	pipex.h get_next_line.h

OBJ		=	$(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

OBJ_B	=	$(addprefix $(SRC_DIR)/, $(SRC_B:.c=.o))

OBJ_GNL	=	$(addprefix $(SRC_DIR)/, $(SRC_GNL:.c=.o))

SRC_DIR	=	src

INC_DIR	=	include

LIBFT	=	$(FT_DIR)/libft.a

FT_DIR	=	libft

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR) -I $(FT_DIR)

LFLAGS	=	-L./libft -lft

RM		=	rm -f

%.o:		%.c $(addprefix $(INC_DIR)/, $(HEADER))
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(OBJ) $(LFLAGS) -o $@

all:		$(NAME)

bonus:		$(OBJ_B) $(LIBFT)
			$(CC) $(OBJ_B) $(LFLAGS) -o $@
			@cp bonus $(NAME)

$(LIBFT):	
			@make -s -C $(FT_DIR)
			@make bonus -s -C $(FT_DIR)

clean:		
			@make clean -s -C $(FT_DIR)
			@$(RM) $(OBJ) $(OBJ_B) $(OBJ_GNL)

fclean:		clean
			@make fclean -s -C $(FT_DIR)
			@$(RM) $(NAME) bonus

re:			fclean all

.PHONY:		all clean fclean re
