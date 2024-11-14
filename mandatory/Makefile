# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/03 15:48:46 by ksellami          #+#    #+#              #
#    Updated: 2024/11/13 17:51:34 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3D.h
FILES = parsing/parse_clrs_txt.c parsing/parse_clrs_txt_utils1.c parsing/check_file.c\
parsing/ft_init.c parsing/parse_map.c parsing/parse_player.c parsing/valid_map.c\
parsing/utils1.c \
main.c get_next_line.c \
libft/libft_tools1.c libft/libft_tools2.c libft/libft_tools3.c\
libft/ft_split.c \
raycasting/texture.c raycasting/image_utils.c \
raycasting/event.c \
raycasting/cast_rays.c raycasting/cast_ray.c\
raycasting/draw.c

OBJS = ${FILES:%.c=%.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

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
