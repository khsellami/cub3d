/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/25 12:39:19 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
#define CUB3D

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif
#include <mlx.h>
#include <libc.h>
#include <math.h>
#define CEILING_COLOR 0xA0C8E0 // Example color for the ceiling (light blue)
#define FLOOR_COLOR 0xA0A0A0 // Example color for the floor (gray)

#define TILE_SIZE 50
#define MAP_NUM_ROWS 14
#define MAP_NUM_COLS 33
#define SW 1650 
#define SH 700
#define FOV_ANGLE (60 * (M_PI / 180))  // Example: 60 degrees in radians

#define WALL_STRIP_WIDTH 4
// #define NUM_RAYS SW / WALL_STRIP_WIDTH
#define NUM_RAYS 120
typedef struct s_ray
{
    float distance; // Distance from the player to the wall hit
    float angle;    // The angle of the ray
} t_ray;
typedef struct s_player
{
    float x;
    float y;
    int radius;
    double rotationAngle;
    float moveSpeed;
    double rotationSpeed;
    void *mlx;
    void *window;
    void *img;
    char *img_data;
    int bpp;
    int line_length;
    int endian;
    char **map;
    t_ray rays[NUM_RAYS];
} t_player;





//////libft//////
void draw_floor_and_ceiling(t_player *player);
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);

char	*get_next_line(int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
int parse_color(char *color_str, int *color);
// t_image *create_image(void *mlx, int width, int height);
// void destroy_image(void *mlx, t_image *img);
// void put_pixel(t_image *img, int x, int y, int color);
// void render(t_image *map_image);

void updatePlayer(char direction);
void readMapFromFile(const char *filename);
int handle_input(int keycode);
long	ft_atoi(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);


#endif