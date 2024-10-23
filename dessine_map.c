/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dessine_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:10:50 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/23 21:27:56 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libc.h>
#include <math.h>
#define TILE_SIZE 50
#define MAP_NUM_ROWS 14
#define MAP_NUM_COLS 33
#define SW 1650 
#define SH 700
#define FOV_ANGLE  60 * (M_PI / 180)
#define WALL_STRIP_WIDTH 4
#define NUM_RAYS SW / WALL_STRIP_WIDTH
#  define BUFFER_SIZE 6

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
} t_player;

typedef struct s_ray
{
    float distance; // Distance from the player to the wall hit
    float angle;    // The angle of the ray
} t_ray;

char	*ft_strchr(char *string, int searchedChar)
{
	int	i;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == searchedChar)
			return (string + i);
		i++;
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		count += 1;
		str += 1;
	}
	return (count);
}

char	*ft_strdup(char *s1)
{
	char	*p;
	int		l;
	int		i;

	i = 0;
	l = ft_strlen(s1) + 1;
	p = (char *) malloc (l);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*k;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = (char *) malloc (i + j + 1);
	if (!k)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		k[j++] = s1[i++];
	i = 0;
	while (s2[i])
		k[j++] = s2[i++];
	k[j] = '\0';
	free(s1);
	s1 = NULL;
	return (k);
}

static char	*ft_read(int fd, char *str)
{
	int		byteread;
	char	*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byteread = 1;
	while (byteread)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == 0)
			break ;
		if (byteread == -1)
			return (free(str), str = NULL, free(buffer), buffer = NULL, NULL);
		buffer[byteread] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n') != NULL)
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (str);
}

static char	*getthisline(char *t)
{
	char	*line;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (!t)
		return (NULL);
	while (t[n] && t[n] != '\n')
		n++;
	if (t[n] == '\n')
		n++;
	line = malloc(n + 1);
	if (!line)
		return (NULL);
	while (i < n)
	{
		line[i] = t[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*rest(char *tmp)
{
	char	*newline_pos;
	char	*rst;

	newline_pos = ft_strchr(tmp, '\n');
	if (!newline_pos)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	newline_pos++;
	rst = ft_strdup(newline_pos);
	if (!rst)
		return (NULL);
	free(tmp);
	tmp = NULL;
	return (rst);
}

char	*get_next_line(int fd)
{
	char		*ln;
	static char	*str;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| fd < 0 || fd > INT_MAX)
	{
		if (str != NULL)
			return (free(str), str = NULL, NULL);
		return (NULL);
	}
	str = ft_read(fd, str);
	if (!str || !*str)
		return (free(str), str = NULL, NULL);
	ln = getthisline(str);
	if (!ln)
		return (free(str), str = NULL, NULL);
	str = rest(str);
	return (ln);
}

void init_player(t_player *p)
{
    p->x = SW / 2;
    p->y = SH / 2;
    p->radius = 3;
    p->rotationAngle = M_PI / 2;
    p->moveSpeed = 2.0;
    p->rotationSpeed = 2 * (M_PI / 180);
}

void clear_image(t_player *player)
{
    int img_size = SW * SH * 4; // 4 bytes per pixel for RGBA
    memset(player->img_data, 0, img_size); // Set all pixels to 0 (black)
}

void put_pixel(t_player *player, int x, int y, int color)
{
    if (x >= 0 && x < SW && y >= 0 && y < SH)
    {
        char *dst = player->img_data + (y * player->line_length + x * (player->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_player(t_player *player)
{
    int color = 0x00FF00;
    int x_center = player->x;
    int y_center = player->y;

    for (int y = -player->radius; y <= player->radius; y++)
    {
        for (int x = -player->radius; x <= player->radius; x++)
        {
            if (x * x + y * y <= player->radius * player->radius)
            {
                put_pixel(player, x_center + x, y_center + y, color);
            }
        }
    }
}

void draw_map(t_player *player)
{
    int i = 0, j, color;
    while (player->map[i])
    {
        j = 0;
        while (player->map[i][j])
        {
            color = (player->map[i][j] == '1') ? 0xFFFFFF : 0x000000; // RED for '1', BLACK for '0'
            for (int y = i * TILE_SIZE; y < (i + 1) * TILE_SIZE; y++)
            {
                for (int x = j * TILE_SIZE; x < (j + 1) * TILE_SIZE; x++)
                {
                    put_pixel(player, x, y, color);
                }
            }
            j++;
        }
        i++;
    }
}

int is_wall(float x, float y, t_player *p)
{
    int mapX = (int)(x / TILE_SIZE);
    int mapY = (int)(y / TILE_SIZE);

    if (mapX < 0 || mapY < 0 || mapX >= MAP_NUM_COLS || mapY >= MAP_NUM_ROWS)
        return 1;
    return (p->map[mapY][mapX] == '1');
}

void cast_ray(t_player *player, t_ray *ray)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float ray_dx = cos(ray->angle);
    float ray_dy = sin(ray->angle);

    while (ray_x >= 0 && ray_x < SW && ray_y >= 0 && ray_y < SH)
    {
        if (is_wall(ray_x, ray_y,player))
        {
            ray->distance = sqrt((ray_x - player->x) * (ray_x - player->x) + (ray_y - player->y) * (ray_y - player->y));
            return;
        }
        ray_x += ray_dx;
        ray_y += ray_dy;
    }
    ray->distance = -1;
}

void cast_all_rays(t_player *player)
{
    float ray_angle = player->rotationAngle - (FOV_ANGLE / 2);
    t_ray rays[NUM_RAYS];

    for (int i = 0; i < NUM_RAYS; i++)
    {
        rays[i].angle = ray_angle;
        cast_ray(player, &rays[i]);
        if (rays[i].distance > 0)
        {
            int ray_end_x = player->x + rays[i].distance * cos(rays[i].angle);
            int ray_end_y = player->y + rays[i].distance * sin(rays[i].angle);
            float step_x = (ray_end_x - player->x) / rays[i].distance;
            float step_y = (ray_end_y - player->y) / rays[i].distance;
            float current_x = player->x;
            float current_y = player->y;
            for (int j = 0; j < rays[i].distance; j++)
            {
                put_pixel(player, (int)current_x, (int)current_y, 0x0000FF);
                current_x += step_x;
                current_y += step_y;
            }
        }
        ray_angle += FOV_ANGLE / NUM_RAYS;
    }
}

int key_eshap(int keycode, t_player *player)
{
    float new_x = player->x;
    float new_y = player->y;

    if (keycode == 123)
        player->rotationAngle -= player->rotationSpeed;
    else if (keycode == 124)
        player->rotationAngle += player->rotationSpeed;
    else if (keycode == 126)
    {
        new_x += cos(player->rotationAngle) * player->moveSpeed;
        new_y += sin(player->rotationAngle) * player->moveSpeed;
    }
    else if (keycode == 125)
    {
        new_x -= cos(player->rotationAngle) * player->moveSpeed;
        new_y -= sin(player->rotationAngle) * player->moveSpeed;
    }
    if (!is_wall(new_x, new_y,player))
    {
        player->x = new_x;
        player->y = new_y;
    }
    clear_image(player);
    draw_map(player); // Redraw the map onto the image
    draw_player(player); // Draw the player onto the image
    cast_all_rays(player);
    mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0); // Display the image
    return (0);
}

int close_window(t_player *player)
{
    if (player->map)
    {
        for (int i = 0; player->map[i]; i++)
        {
            free(player->map[i]);
        }
        free(player->map);
    }
    mlx_destroy_window(player->mlx, player->window);
    exit(0);
    return 0;
}

int ft_read_map(char *file, t_player *player)
{
    int fd;
    char *line;
    int i = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return -1;
    }
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '1' || line[0] == ' ')
            i++;
        free(line);
        line = get_next_line(fd);
    }
    // Allocate memory for the map
    player->map = malloc(sizeof(char *) * (i + 1));
    if (!player->map)
    {
        close(fd);
        printf("Error allocating memory for map\n");
        return -1;
    }
    // Reset file pointer
    lseek(fd, 0, SEEK_SET);
    int j = 0;
    line = get_next_line(fd);
    while (line && j < i) {
        if (line[0] == '1' || line[0] == ' ')
        {
            player->map[j] = malloc(strlen(line) + 1);
            if (!player->map[j])
            {
                for (int k = 0; k < j; k++)
                    free(player->map[k]);
                free(player->map);
                close(fd);
                printf("Error allocating memory for map line\n");
                return -1;
            }
            strcpy(player->map[j], line);

            // Check for 'N' in the current line
            char *n_pos = strchr(player->map[j], 'N');
            if (n_pos) {
                // Calculate player position in pixels based on 'N' location
                int x_pos = n_pos - player->map[j]; // Column index of 'N'
                int y_pos = j; // Row index of 'N'

                // Set the player's position in the map
                player->x = (x_pos * TILE_SIZE) + (TILE_SIZE / 2);
                player->y = (y_pos * TILE_SIZE) + (TILE_SIZE / 2);

                // Replace 'N' with '0' so it's treated as an empty space
                *n_pos = '0';
            }

            j++;
        }
        free(line);
        line = get_next_line(fd);
    }

    // Null terminate the map
    player->map[j] = NULL;

    close(fd);
    return 0;
}

int main(int ac , char **av)
{
    (void)ac;
    t_player p;
    
    init_player(&p);
    if (ft_read_map(av[1], &p) == -1)
    {
        printf("Error reading map\n");
        return EXIT_FAILURE;
    }
    p.mlx = mlx_init();
    if (!(p.mlx))
        return (0);
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!(p.window))
        return (0);
    
    p.img = mlx_new_image(p.mlx, SW, SH);
    p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
    clear_image(&p);
    draw_map(&p);
    draw_player(&p);
    cast_all_rays(&p);
    mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
    mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
    mlx_hook(p.window, 17, 0, close_window, &p);
    mlx_loop(p.mlx);
    return (0);
}

//coding the field of view ray increments
//4 raycasting ==>> video 4  