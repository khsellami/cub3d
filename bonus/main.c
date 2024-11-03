/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 18:57:23 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void clear_image(t_player *player)
{
    int img_size = SW * SH * 4;
    memset(player->img_data, 0, img_size);
}

void clear_screen(t_player *player)
{
    int color = 0x000000;
    for (int y = 0; y < SH; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            put_pixel(player, x, y, color);
        }
    }
}

int get_pixel_color(void *img, int x, int y, t_player *p) 
{
    char *data = mlx_get_data_addr(img, &p->bpp, &p->line_length, &p->endian);
    return *(int*)(data + (y * p->line_length + x * (p->bpp / 8)));
}

void init_player(t_player *player)
{
    player->mlx = mlx_init();
    if (!player->mlx)
    {
        printf("Erreur: Échec de l'initialisation de MiniLibX\n");
        exit(EXIT_FAILURE);
    }
}
int is_wall(double x, double y, t_player *p)
{
    int mapX = (int)(x / TILE_SIZE);
    int mapY = (int)(y / TILE_SIZE);

    if (mapY < 0 || mapY >= MAP_NUM_ROWS || mapX < 0 || mapX >= MAP_NUM_COLS || 
        p->map == NULL || p->map[mapY] == NULL || 
        mapX >= (int)strlen(p->map[mapY])) 
        return 1;
    return (p->map[mapY][mapX] == '1');
}
void draw_rectangle(t_img *img, int x, int y, int width, int height, int color)
{
    int i, j;
    uint32_t *data;

    // Ensure the rectangle is within the image bounds
    if (x < 0 || y < 0 || x + width > img->width || y + height > img->height)
        return;

    data = (uint32_t *)img->data; // Assuming data is in a format compatible with uint32_t

    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            data[(y + j) * img->line_length / 4 + (x + i)] = color; // Set the color
        }
    }
}
int main(int ac, char **av)
{
    t_player p;

    if (ac != 2)
        return (ft_putstr_fd("USAGE: .cub3D <name_map.cub>\n", 2), 1);
    if (checkfilename(av[1]) == -1)
        return (ft_putstr_fd("Invalid extension file name\n", 2), 1);
    init_data(&p);
    if (ft_read_map(av[1], &p) == -1)
        return (ft_putstr_fd("Error reading map\n", 2), 1);
    if (!valid_map(&p))
        return (write(2, "Invalid map\n", 12), 1);
    p.mlx = mlx_init();
    if (!p.mlx) {
        printf("Erreur: Échec de l'initialisation de MiniLibX\n");
        return 1;
    }
    init_textures(&p);
    init_player_sprite(&p); 
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!p.window)
        return (1);
    p.img = mlx_new_image(p.mlx, SW, SH);
    p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
    clear_image(&p);
    draw_map(&p);
     draw_mini_map(&p);
     cast_all_rays(&p);
   
    draw_player(&p);
    mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
    mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
    mlx_hook(p.window, 17, 0, close_window, &p);
    mlx_loop(p.mlx);
    return (0);
}