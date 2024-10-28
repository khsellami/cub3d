/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 11:31:14 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
#define CUB3D

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif
# include <mlx.h>
# include <libc.h>
# include <math.h>

# define SW 800
# define SH 600
# define CEILING_COLOR 0xA0C8E0
# define FLOOR_COLOR 0xA0A0A0
# define TILE_SIZE 32
# define MAP_NUM_ROWS 14
# define MAP_NUM_COLS 33
# define FOV_ANGLE (60 * (M_PI / 180))
# define WALL_STRIP_WIDTH 4
# define NUM_RAYS SW / WALL_STRIP_WIDTH

typedef struct s_ray
{
	int horizontal_distance;
	int vertical_distance;
	float distance;
	float angle;
} t_ray;

typedef struct s_player
{
	float angle;
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
	//textures
	char *no;
	char *so;
	char *ea;
	char *we;
	//colors
	int floor_color;
	int ciel_color;
	t_ray rays[NUM_RAYS];
} t_player;

////////LIBFT_FUNCTIONS////////
int		ft_strlcpy(char *dst, char *src, int dstsize);
char	**ft_split(char *s, char c);
long	ft_atoi(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
void	*ft_memcpy(void *dst, void *src, int n);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);

////////GET_NEXT_LINE////////
char	*get_next_line(int fd);

////////PARSING////////
int		checkfilename(char *filename);
int 	valid_map(t_player *p);
int 	valid_char_map(char c);
int 	not_mur_or_space(char c);
int 	valid_space(t_player *p, int i, int j);
int 	entoure_mur(t_player *p, int i, int j);

////////READ MAP////////
int 	ft_read_map(char *file, t_player *player);
int 	is_valid_color(int color);
int 	parse_color(char *line, int *color);
void 	set_player_orientation(t_player *player, char orientation);
int 	parse_textures(char *line, char **texture_path);
int 	parse_line(char *line, t_player *player);

////////UTILS////////
int array_len(char **array);
void free_array(char **array);

////////INIT////////
void init_data(t_player *p);
//
void draw_floor_and_ceiling(t_player *player);
char	*get_next_line(int fd);
int parse_color(char *color_str, int *color);
void updatePlayer(char direction);
void readMapFromFile(const char *filename);
int handle_input(int keycode);


#endif