/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:49:50 by ksellami         ###   ########.fr       */
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
    char    **map;//// 2D array of strings for the game map
    double  player_x;
    double  player_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    char *texture_north;      // Texture path for the north direction
    char *texture_south;      // Texture path for the south direction
    char *texture_west;       // Texture path for the west direction
    char *texture_east;       // Texture path for the east direction
    int floor_color;          // RGB color value for the floor (packed as a single integer)
    int ceiling_color;        // RGB color value for the ceiling (packed as a single integer)
    
} t_game;

//////libft//////
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, int n);
int	ft_atoi(char *str);
char	**ft_split(char *s, char c);
int	ft_strlcpy(char *dest, char *src, int size);

//////parsing//////
int valid_file_name(char *f);
int init_game(t_game *game, char *map_file);
int parse_map(t_game *game, char *map_file);
int is_texture_line(char *line);
int is_color_line(char *line);
int is_map_line(char *line);
int ft_str_only_contains_spaces(char *str);
void parse_texture(t_game *game, char *line);
void parse_color(t_game *game, char *line);
void add_line_to_map(t_game *game, char *line, int index);
int valid_map(t_game *game);
void render3d(t_game *game);


//////get_next_line//////
char	*get_next_line(int fd);


#endif