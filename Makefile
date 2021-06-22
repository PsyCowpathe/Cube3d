# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 20:07:53 by agirona           #+#    #+#              #
#    Updated: 2021/06/22 16:50:42 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= cub3d.c parsing.c init.c raycasting.c draw.c dynamique_error.c \
		  event.c get_key.c map_parsing.c moov.c hud.c parsing_utility.c \
		  screenshot.c utility.c secondary_utility.c sprite.c sprite_utility.c \
		  static_error.c third_utility.c

SRCS_DIR = src

OBJS	=	$(SRCS:.c=.o)

OBJS_DIR	= obj

OBJS_PATH	= $(addprefix $(OBJS_DIR)/, $(OBJS))

INC		= include

LIBFT = dependency/libft/libft.a 

MLX = dependency/mlx/libmlx.a

FRAMEWORK = -framework OpenGL -framework Appkit

CFLAGS	= -Wall -Wextra -Werror -I $(INC)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC)
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : 	$(OBJS_PATH) $(LIBFT) $(MLX)
			gcc $(FRAMEWORK) $(OBJS_PATH) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT) :	
			$(MAKE) -C dependency/libft

$(MLX) :
			$(MAKE) -C dependency/mlx

clean:
			rm -f $(OBJS_PATH)
			$(MAKE)	-C dependency/libft clean
			$(MAKE)	-C dependency/mlx clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C dependency/libft fclean

re:			fclean all

.PHONY:		all clean fclean re
