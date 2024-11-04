# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/03 15:48:46 by ksellami          #+#    #+#              #
#    Updated: 2024/11/03 20:55:46 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3D.h
FILES = main.c get_next_line.c libft_tools1.c \
file_error.c ft_init.c ft_split.c \
valid_map.c \
parse_clr_txt.c parse_clr_txt_utils.c \
parse_player.c parse_map.c \
utils1.c \
texture.c \
image_utils.c \
event.c \
cast_rays.c cast_ray.c\
draw.c

OBJS = ${FILES:%.c=%.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJS} 

fclean: clean
	rm -f ${NAME}
	
re: fclean all
