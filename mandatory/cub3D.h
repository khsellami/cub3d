/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 21:05:41 by ksellami         ###   ########.fr       */
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
// # define CEILING_COLOR 0xA0C8E0
// # define FLOOR_COLOR 0xA0A0A0
# define TILE_SIZE 32
# define MAP_NUM_ROWS 14
# define MAP_NUM_COLS 33
#define FOV_ANGLE (M_PI / 3)
# define WALL_STRIP_WIDTH 4
#define NUM_RAYS 1000
typedef struct s_img {
    void *img;
    int width;
    int height;
    char *data;
    int bpp;
    int line_length;
    int endian;
} t_img;

typedef struct s_texture {
    t_img *img;
    int width;
    int height;
    char *data;
    int line_length;
} t_texture;
typedef struct s_ray
{
	double horz_x;
    double horz_y;
    double vert_x;
    double vert_y;
	double horizontal_distance;
	double vertical_distance;
	double distance;
	double angle;
} t_ray;

typedef struct s_player
{
	//moves
	int move_left ;
 	int move_right;
	int move_up;
	int move_down;
//...
	double angle;
	double x;
	double y;
	int radius;
	double rotationAngle;
	double moveSpeed;
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
	//add
	 t_img no_img;  // North texture
    t_img so_img;  // South texture
    t_img ea_img;  // East texture
    t_img we_img;  // West texture
    int width_no, height_no;
    int width_so, height_so;
    int width_ea, height_ea;
    int width_we, height_we;
	t_img texture[4];
	
	//add
	//colors
	int floor_color;
	int ciel_color;
	 t_texture textures[4];
	t_ray rays[NUM_RAYS];
} t_player;

typedef struct s_data
{
    double angle_diff;
    double corrected_distance;
    int wall_height;
    int wall_top;
    int wall_bottom;
    int x_pos;
    int texture_index;
    int texture_x;
    int texture_y;
	int x;
    int y;
    int px;
    int py;
	int color;
    int tex_y;
    int tex_x;
	int y_offset;
	int x_offset;
} t_data;

//GET NEXT LINE
char	*get_next_line(int fd);

//LIBFT
char	*ft_strtrim(char *s1, char *set);
int	ft_strncmp(char *s1, char *s2, int n);
int	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
void	*ft_memcpy(void *dst, void *src, int n);
void	ft_putstr_fd(char *s, int fd);
int	ft_strcmp(char *s1, char *s2);
char	**ft_split(char *s, char c);

//PARSING
int	checkfilename(char *filename);
void init(t_player *p);
int valid_map(t_player *p);
int valid_char_map(char c);
int not_mur_or_space(char c);
int valid_space(t_player *p, int i, int j);
int entoure_mur(t_player *p, int i, int j);
int parse_colors_textures(int ac, char **av, t_player *p);
char *parse_texture(char *line);
int is_valid_color(int color);
int parse_color(char *line, int *color);
int check_clr_txt(t_player *p);
int check_one_player(t_player *p);
void stocke_map_line(char *line, int size, t_player *p, int j);
int just_spaces(char *s);
int ft_parsing(int ac , char **av , t_player *p);
int array_len(char **array);
void free_array(char **array);
void init_player(t_player *p, int x, int y, char direction);


//TEXTURES
void init_textures(t_player *player);
int load_texture(t_player *player, char *path, t_img *texture);
t_img *get_texture(t_player *player, int ray_id);
int calculate_texture_x(t_player *player, int ray_id, t_img *texture);

//EVENTS
int key_eshap(int keycode, t_player *player);
void exit_game(t_player *player);
int close_window(t_player *player);

//RAYCASTING
void cast_all_rays(t_player *player);
int is_wall(double x, double y, t_player *p);
double normalize_angle(double angle);
void horizontal_ray_intersection(t_player *player, t_ray *ray);
void vertical_ray_intersection(t_player *player, t_ray *ray);
void cast_ray(t_player *player, t_ray *ray);

//DRAW
void draw_floor_and_ceiling(t_player *player);
void render_3d_wall_slice(t_player *player, int ray_id, double distance);
void render_wall_slice(t_player *player, t_data *data, t_img *texture);
void calculate_wall_properties(t_player *player, int ray_id, double distance, t_data *data);

//UTILS
void clear_image(t_player *player);
void clear_screen(t_player *player);
void put_pixel(t_player *player, int x, int y, int color);

#endif