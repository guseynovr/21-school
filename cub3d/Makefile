NAME		=	cub3d

INCLUDE_DIR	=	inc

BONUS_DIR	= 	bonus

MANDTR_DIR	=	mandatory

INCS		=	render.h		\
				parse.h			\
				events.h		\
				draw.h			\
				draw_utils.h	\
				settings.h		\
				map.h			\
				event_utils.h	\
				utils.h			\
				init_r_data.h
				
HEADER		=	$(addprefix $(INCLUDE_DIR)/$(MANDTR_DIR)/, $(INCS))

HEADER_B	=	$(addprefix $(INCLUDE_DIR)/$(BONUS_DIR)/, $(INCS))

SRC_DIR		=	src/cub3d

CFILES		=	parse.c				\
				service.c			\
				elem_func_color.c	\
				elem_func_texture.c	\
				parse_map.c			\
				parse_map_utils.c	\
				parse_elem.c		\
				parse_map_check.c	\
				start.c				\
				init.c				\
				init_utils.c		\
				init_r_data.c		\
				cast.c				\
				cast_utils.c		\
				draw.c				\
				draw_utils.c		\
				events.c			\
				event_utils.c		\
				utils.c				\
				main.c

CFILES_B	=	parse.c				\
				service.c			\
				elem_func_color.c	\
				elem_func_texture.c	\
				parse_map.c			\
				parse_map_utils.c	\
				parse_elem.c		\
				parse_map_check.c	\
				start.c				\
				init.c				\
				init_utils.c		\
				init_r_data.c		\
				cast.c				\
				cast_utils.c		\
				draw.c				\
				draw_utils.c		\
				events.c			\
				event_utils.c		\
				utils.c				\
				minimap.c			\
				main.c

SRCS		=	$(addprefix $(SRC_DIR)/$(MANDTR_DIR)/, $(CFILES))

SRCS_B		=	$(addprefix $(SRC_DIR)/$(BONUS_DIR)/, $(CFILES_B))
				
OBJS_DIR	=	objects/cub3d/mandatory/

OBJS_DIR_B	=	objects/cub3d/bonus/

MLX_FLAGS	=	-framework OpenGL -framework AppKit -lmlx

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -O3

RM			=	rm -f

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:c=o))

OBJS_B		=	$(addprefix $(OBJS_DIR_B), $(SRCS_B:c=o))

LIBFT_DIR	=	src/libft

LIBFT		=	libft.a

GNL_DIR		=	src/gnl

GNL			=	libgnl.a

MLX_DIR		=	src/mlx

MLX			=	$(MLX_DIR)/libmlx.a


$(OBJS_DIR)%.o:		%.c $(HEADER)
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)/$(MANDTR_DIR) -Iinc -I$(MLX_DIR)

$(OBJS_DIR_B)%.o:	%.c $(HEADER_B)
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)/$(BONUS_DIR) -Iinc -I$(MLX_DIR)

$(NAME):			$(GNL) $(LIBFT) $(OBJS) $(HEADER_B) $(MLX)
					$(CC) $(OBJS) $(MLX_FLAGS) -lft -lgnl -L. -Lsrc/mlx -o $@

all:				$(NAME)

bonus:				$(GNL) $(LIBFT) $(OBJS_B) $(HEADER_B) $(MLX)
					$(CC) $(OBJS_B) $(MLX_FLAGS) -lft -lgnl -L. -Lsrc/mlx -o $@
					@cp bonus $(NAME)

$(GNL):
					make -C $(GNL_DIR)

$(LIBFT):
					make -C $(LIBFT_DIR)

$(MLX):
					make -C $(MLX_DIR)

clean:
					make clean -C $(LIBFT_DIR)
					make clean -C $(GNL_DIR)
					$(RM) $(OBJS)
					$(RM) $(OBJS_B)

fclean: 			clean
					make fclean -C $(LIBFT_DIR)
					make fclean -C $(GNL_DIR)
					@$(RM) bonus
					$(RM) $(NAME)

re: 				fclean all

.PHONY: 			all clean fclean re
