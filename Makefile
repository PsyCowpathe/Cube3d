# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 20:07:53 by agirona           #+#    #+#              #
#    Updated: 2021/06/21 20:20:11 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCS	= cub3d.c parsing.c init.c raycasting.c draw.c dynamique_error.c \
		  event.c get_key.c map_parsing.c moov.c hud.c parsing_utility.c \
		  screenshot.c utility.c secondary_utility.c sprite.c sprite_utility.c \
		  static_error.c third_utility.c

OBJS	= ${SRCS:.c=.o}

INC		= libft.h

CFLAGS	= -Wall -Wextra -Werror -Imlx

%.o: %.c ${INC}
	gcc $(CFLAGS)

all: $(NAME)

$(NAME) :	${OBJS}
			gcc $(CFLAGS) -o $(NAME)

clean:
			rm -f ${OBJS}
			$(MAKE)	-C libft clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C libft fclean

re:			fclean all
			$(MAKE)	-C libft re

.PHONY:		all clean fclean re
