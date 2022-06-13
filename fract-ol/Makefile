NAME	=	fractol

HEADER	=	fractol.h colors.h 

INC_DIR	=	include

MLX		=	mlx/libmlx.a

LIBFT	=	libft/libft.a

SRC		=	main.c colors.c fractals.c events.c	\
			events_mandelbrot.c events_julia.c	\
			draw.c utils.c

SRC_DIR	=	src

OBJ		=	$(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -O3 $(INCLUDE)

INCLUDE	=	-Imlx -Ilibft -Iinclude

FWS		=	-framework OpenGL -framework AppKit

LFLAGS	=	-lmlx -Lmlx -lft -Llibft

RM		=	rm -f

%.o:		%.c $(addprefix $(INC_DIR)/, $(HEADER))
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJ) $(MLX) $(LIBFT) $(addprefix $(INC_DIR)/, $(HEADER))
			$(CC) $(OBJ) $(LFLAGS) $(FWS) -o $@

#$(NAME):	$(OBJ) $(LIBFT) $(addprefix $(INC_DIR)/, $(HEADER))
			$(CC) $(OBJ) $(LFLAGS) $(FWS) -o $@

all:		$(NAME)

$(MLX):		
			@make -s -C mlx

$(LIBFT):	
			@make -s -C libft

clean:		
			@make clean -s -C libft
			$(RM) $(OBJ)

fclean:		clean
			make clean -C mlx
			@make fclean -s -C libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re bonus
