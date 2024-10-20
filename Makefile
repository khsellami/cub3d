# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/19 17:16:24 by ksellami          #+#    #+#              #
#    Updated: 2024/10/20 13:49:02 by ksellami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3D.h
FILES =   main.c \
libft/libft_tools1.c libft/libft_tools2.c libft/ft_atoi.c libft/ft_split.c\
parsing/checkFileName.c parsing/init.c parsing/parse_map.c parsing/checkValidMap.c\
get_next_line.c \
raycasting/test.c

OBJS = ${FILES:%.c=%.o}
CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

all : $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ${OBJS} 

fclean: clean
	rm -f ${NAME}
	
re: fclean all