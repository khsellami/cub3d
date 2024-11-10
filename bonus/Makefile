# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/03 15:48:46 by ksellami          #+#    #+#              #
#    Updated: 2024/11/10 09:16:23 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS_NAME = cub3D_bonus

HEADER = cub3D_bonus.h
BONUS_HEADER = cub3D_bonus.h

FILES = parsing/parse_clrs_txt.c parsing/parse_clrs_txt_utils1.c parsing/check_file.c\
parsing/ft_init.c parsing/parse_map.c parsing/parse_player.c parsing/valid_map.c\
parsing/utils1.c \
main.c get_next_line.c \
libft/libft_tools1.c libft/libft_tools2.c libft/libft_tools3.c\
libft/ft_split.c \
raycasting/texture.c raycasting/image_utils.c \
raycasting/event.c \
raycasting/cast_rays.c raycasting/cast_ray.c\
raycasting/draw.c \
minimap.c \
sprite.c \
mouse.c

BONUS_FILES = $(FILES)

BONUS_OBJS = ${BONUS_FILES:%.c=%.o}

CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

all: $(BONUS_NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(BONUS_HEADER)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME) -lmlx -framework OpenGL -framework AppKit
%.o: %.c $(HEADER) $(BONUS_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f ${BONUS_OBJS}
fclean: clean
	rm -f ${BONUS_NAME}
re: fclean all
