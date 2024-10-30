# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 17:16:24 by ksellami          #+#    #+#              #
#    Updated: 2024/10/29 13:19:51 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D_bonus
HEADER = cub3D_bonus.h
FILES = main.c \
libft/libft_tools1.c libft/libft_tools2.c libft/libft_tools3.c libft/ft_split.c \
get_next_line.c \
check_map.c check_map_utils.c \
read_map.c read_map_utils.c \
utils1.c \
init.c \
raycast.c \
render.c \
render2.c \
texture.c \
event.c

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
