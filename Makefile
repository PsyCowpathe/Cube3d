# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 20:07:53 by agirona           #+#    #+#              #
#    Updated: 2021/06/21 20:56:46 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= cub3d.c parsing.c init.c raycasting.c draw.c dynamique_error.c \
		  event.c get_key.c map_parsing.c moov.c hud.c parsing_utility.c \
		  screenshot.c utility.c secondary_utility.c sprite.c sprite_utility.c \
		  static_error.c third_utility.c

INC		= libft.h

LIBFT = libft/libft.a 

MLX = mlx/libmlx.a

FRAMEWORK = -framework OpenGL -framework Appkit

CFLAGS	= -Wall -Wextra -Werror -Imlx $(FRAMEWORK) -I $(INC)

%.o: %.c ${INC}
	gcc $(CFLAGS)

all: $(NAME)

$(NAME) :	$(LIBFT) $(MLX) ${SRCS}
			gcc $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT) $(MLX)

$(LIBFT) :	
			$(MAKE) -C libft

$(MLX) :
			$(MAKE) -C mlx

clean:
			$(MAKE)	-C libft clean
			$(MAKE)	-C mlx clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C libft fclean

re:			fclean all
			$(MAKE)	-C libft re
			$(MAKE)	-C mlx re

.PHONY:		all clean fclean re
