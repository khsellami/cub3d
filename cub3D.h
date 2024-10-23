/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/23 17:55:50 by kahmada          ###   ########.fr       */
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
#include <stdbool.h>
#include <string.h>

#define TILE_SIZE 32
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define GREEN_PIXEL 0xFF00
#define RED 0xFF0000
#define WHITE_PIXEL 0xFFFFFF
#define WALL 0x5454C5
#define SPACE 0x639CD9
#define YELLOW 0xFFFF00
#define DARK_YELLOW 0xd7d708
#define DARK 0x342056
#define GRID_SIZE 32

#define LEFT_ARROW 123
#define RIGHT_ARROW 124

#define ESC 53
#define W_KEY 13
#define D_KEY 2
#define S_KEY 1
#define A_KEY 0

#define MOVE_STEP 4
#define VIEW_ANGLE 1.0472
#define NBR_RAYS WINDOW_WIDTH

// typedef struct s_image {
//     void *img;
//     char *data;
//     int width;
//     int height;
//     int bpp;
//     int size_line;
//     int endian;
// } t_image;
typedef struct s_textures {
    char *north;
    char *south;
    char *west;
    char *east;
    char *wall;   // Add wall texture path
    char *floor;  // Add floor texture path
    char *player; // Add player texture path
} t_textures;


typedef struct s_img {
    void *img_ptr;
    char *pixel_ptr;
    int bit_par_px;
    int bit_order;
    int pix_len;
} t_img;

typedef struct p {
    char **map;         // 2D array for the game map
    char **map2;        // Possibly a duplicate or a secondary map
    int sol[3];         // Might be used for solution colors or coordinates
    int ciel[3];        // Ceiling color, but it's unclear what the context is
    void *mlx_conex;    // Connection to the MLX
    void *mlx_window;   // Pointer to the MLX window
    t_img img;          // Image structure for rendering
    t_textures textures; // Textures for the map (north, south, etc.)
    int floor;          // Floor color (stored as an int representing RGB)
    int ceiling;        // Ceiling color (stored as an int representing RGB)
    float x;            // Player's x-coordinate
    float y;            // Player's y-coordinate
    int size_f;        // Possibly the size of the floor (ambiguous)
    int height;        // Height of the map or player view
    float moveSpeed;   // Speed of player movement
} Player;



//////libft//////
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
int ft_make_texture(Player *player, int j);
char	*get_next_line(int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
int parse_color(char *color_str, int *color);
// t_image *create_image(void *mlx, int width, int height);
// void destroy_image(void *mlx, t_image *img);
// void put_pixel(t_image *img, int x, int y, int color);
// void render(t_image *map_image);
bool isCollidingWithWall(float newX, float newY);
void updatePlayer(char direction);
void readMapFromFile(const char *filename);
int handle_input(int keycode);
long	ft_atoi(char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int ft_read_map(char *file, Player *player);


#endif