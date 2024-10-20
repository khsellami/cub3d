/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 11:46:58 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
#define CUB3D

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>


typedef struct s_game
{
    void    *mlx;
    void    *window;
    int     width;
    int     height;
    char    **map;
    double  player_x;
    double  player_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;

    
} t_game;

//////libft//////
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);

//////parsing//////
int valid_file_name(char *f);
int init_game(t_game *game, char *map_file);
int parse_map(t_game *game, char *map_file);

//////get_next_line//////
char	*get_next_line(int fd);


#endif