/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/13 17:23:46 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <stdio.h>
# define BUFFER_SIZE 6
# define SW 1900
# define SH 1000
# define TILE_SIZE 32
# define FOV_ANGLE (M_PI / 3)
# define NUM_RAYS SW

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	*img;
	int		width;
	int		height;
	char	*data;
	int		line_length;
}	t_texture;

typedef struct s_ray
{
	double	horz_x;
	double	horz_y;
	double	vert_x;
	double	vert_y;
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;
	double	angle;
	int		israyfacingdown;
	int		israyfacingup;
	int		israyfacingright;
	int		israyfacingleft;
	double	xintercept;
	double	yintercept;
}	t_ray;

typedef struct s_player
{
	int			move_left;
	int			move_right;
	int			move_up;
	int			move_down;
	double		angle;
	double		x;
	double		y;
	double		rotationangle;
	double		movespeed;
	double		rotationspeed;
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_length;
	int			endian;
	char		**map;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	t_img		no_img;
	t_img		so_img;
	t_img		ea_img;
	t_img		we_img;
	int			width_no;
	int			height_no;
	int			width_so;
	int			height_so;
	int			width_ea;
	int			height_ea;
	int			height_we;
	int			width_we;
	t_img		texture[4];
	int			floor_color;
	int			ciel_color;
	t_texture	textures[4];
	t_ray		rays[NUM_RAYS];
	int map_row;
	int map_col;
}	t_player;

typedef struct s_data
{
	double	angle_diff;
	double	corrected_distance;
	double	wall_height;
	int		wall_top;
	int		wall_bottom;
	int		x_pos;
	int		y_pos;
	int		texture_index;
	int		texture_x;
	int		texture_y;
	int		x;
	int		y;
	int		px;
	int		py;
	int		color;
	int		tex_y;
	int		tex_x;
	int		y_offset;
	int		x_offset;
	char	*n_pos;
	char	*s_pos;
	char	*e_pos;
	char	*w_pos;
	int count;
}	t_data;

char	**ft_split(char *s, char c);
char	*ft_strtrim(char *s1, char *set);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *string, int searchedChar);
char	*ft_strdup(char *s1);
void	*ft_memcpy(void *dst, void *src, int n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		checkfilename(char *filename);
void	init_player(t_player *p);
void	init_rays(t_player *p);
int		init(t_player *p);
char	*parse_texture(char *line);
int		is_valid_color(int color);
int		parse_color(char *line, int *color);
int		check_clr_txt(t_player *p);
void	parse_texture_line(char *trimmed, t_player *p);
int		parse_color_line(char *trimmed, t_player *p);
int		parse_colors_textures(char **av, t_player *p);
void	stocke_map_line(char *line, int size, t_player *p, int j);
int		just_spaces(char *s);
int		count_map_lines(int fd, int *longest_line);
void	read_map_lines(int fd, int longest_line, t_player *p);
int		ft_read_map(char **av, t_player *p);
void	update_player(t_player *p, char direction);
int		found_player(char c);
int		check_one_player(t_player *p);
int		array_len(char **array);
void	free_array(char **array);
int		valid_char_map(char c);
int		not_mur_or_space(char c);
int		valid_space(t_player *p, int i, int j);
int		entoure_mur(t_player *p, int i, int j);
int		valid_map(t_player *p);
void	find_horizontal_intersection(t_player *player, t_ray *ray, \
double xstep, double ystep);
void	horizontal_ray_intersection(t_player *player, t_ray *ray);
void	find_vertical_intersection(t_player *player, t_ray *ray, \
double xstep, double ystep);
void	vertical_ray_intersection(t_player *player, t_ray *ray);
void	cast_ray(t_player *player, t_ray *ray);
double	ft_dist(double x1, double y1, double x2, double y2);
void	determine_ray_facing_direction(t_ray *ray);
double	normalize_angle(double angle);
int		is_wall(double x, double y, t_player *p);
void	cast_all_rays(t_player *player);
void	draw_floor_and_ceiling(t_player *player);
void	calculate_wall_properties(t_player *player, int ray_id, \
double distance, t_data *data);
void	render_wall_slice(t_player *player, t_data *data, t_img *texture);
void	render_3d_wall_slice(t_player *player, int ray_id, double distance);
int		close_window(t_player *player);
void	exit_game(t_player *player);
void	rotate_player(int keycode, t_player *player);
void	move_player(int keycode, t_player *player);
int		key_eshap(int keycode, t_player *player);
void	clear_image(t_player *player);
void	clear_screen(t_player *player);
void	put_pixel(t_player *player, int x, int y, int color);
int		load_texture(t_player *player, char *path, t_img *texture);
void	init_textures(t_player *player);
t_img	*get_texture(t_player *player, int ray_id);
int		calculate_texture_x(t_player *player, int ray_id, t_img *texture);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dest, char *src);
void	*ft_memset(void *s, int c, int n);
int		ft_atoi(char *str);

#endif