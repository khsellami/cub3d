/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 16:02:20 by ksellami         ###   ########.fr       */
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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60.0
#define KEY_W 119  // Move forward
#define KEY_S 115  // Move backward
#define KEY_A 97   // Turn left
#define KEY_D 100  // Turn right
#define KEY_ESC 65307 // Escape key
#define speed 1
#define KeyPress 2           // Key press event
#define KeyPressMask (1L<<0) // Key press mask
#define DestroyNotify 17     // Window close event
#define NoEventMask 0        // No event mask


typedef struct s_player
{
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_game
{
    void    *mlx;
    void    *window;
    char    **map;
    char *texture_north;      // Texture path for the north direction
    char *texture_south;      // Texture path for the south direction
    char *texture_west;       // Texture path for the west direction
    char *texture_east;       // Texture path for the east direction
    int floor_color;          // RGB color value for the floor (packed as a single integer)
    int ceiling_color;        // RGB color value for the ceiling (packed as a single integer)
    t_player player;
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
int init_game(t_game *game);
int parse_map(t_game *game, char *map_file);
int is_texture_line(char *line);
int is_color_line(char *line);
int is_map_line(char *line);
int ft_str_only_contains_spaces(char *str);
void parse_texture(t_game *game, char *line);
void parse_color(t_game *game, char *line);
void add_line_to_map(t_game *game, char *line, int index);
int valid_map(t_game *game);
int render3d(void *param);


//////get_next_line//////
char	*get_next_line(int fd);


#endif