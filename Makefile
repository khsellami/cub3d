# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 18:59:05 by kahmada           #+#    #+#              #
#    Updated: 2024/11/16 21:55:55 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = cub3d
BONUS_NAME = cub3D_bonus
CC         = cc
CFLAGS     = -Wall -Werror -Wextra
RM         = rm -f

SRC = mandatory/parsing/parse_clrs_txt.c mandatory/parsing/parse_clrs_txt_utils1.c mandatory/parsing/check_file.c \
mandatory/parsing/ft_init.c mandatory/parsing/parse_map.c mandatory/parsing/parse_player.c mandatory/parsing/valid_map.c \
mandatory/parsing/utils1.c \
mandatory/main.c mandatory/get_next_line.c \
mandatory/libft/libft_tools1.c mandatory/libft/libft_tools2.c mandatory/libft/libft_tools3.c \
mandatory/libft/ft_split.c \
mandatory/raycasting/texture.c mandatory/raycasting/image_utils.c \
mandatory/raycasting/event.c \
mandatory/raycasting/cast_rays.c mandatory/raycasting/cast_ray.c \
mandatory/raycasting/draw.c

SRC_BONUS = bonus/parsing/parse_clrs_txt.c bonus/parsing/parse_clrs_txt_utils1.c bonus/parsing/check_file.c \
bonus/parsing/ft_init.c bonus/parsing/parse_map.c bonus/parsing/parse_player.c bonus/parsing/valid_map.c \
bonus/parsing/utils1.c \
bonus/main.c bonus/get_next_line.c \
bonus/libft/libft_tools1.c bonus/libft/libft_tools2.c bonus/libft/libft_tools3.c \
bonus/libft/ft_split.c \
bonus/raycasting/texture.c bonus/raycasting/image_utils.c \
bonus/raycasting/event.c \
bonus/raycasting/cast_rays.c bonus/raycasting/cast_ray.c \
bonus/raycasting/draw.c \
bonus/minimap.c \
bonus/sprite.c \
bonus/mouse.c

OBJ = $(SRC:.c=.o)
B_OBJ = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

$(BONUS_NAME): $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) -o $(BONUS_NAME) -lmlx -framework OpenGL -framework AppKit

mandatory/%.o: mandatory/%.c mandatory/cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@


bonus/%.o: bonus/%.c bonus/cub3D_bonus.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ) $(B_OBJ)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all