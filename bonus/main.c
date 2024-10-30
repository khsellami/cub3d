/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/29 14:15:36 by kahmada          ###   ########.fr       */
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
int is_wall(float x, float y, t_player *p)
{
    int mapX = (int)(x / TILE_SIZE);
    int mapY = (int)(y / TILE_SIZE);
    if (mapY < 0 || mapY >= MAP_NUM_ROWS || 
        mapX < 0 || mapX >= MAP_NUM_COLS || 
        p->map == NULL || 
        p->map[mapY] == NULL || 
        mapX >= (int)strlen(p->map[mapY])) 
    {
        return 1;
    }
    return (p->map[mapY][mapX] == '1');
}
void draw_minimap(t_player *player) {
    int color;
    int i, j;
    int mini_tile_size = MINIMAP_SIZE / (player->map_width > 0 ? player->map_width : 1);
    
    for (i = 0; player->map[i]; i++) {
        for (j = 0; player->map[i][j]; j++) {
            color = (player->map[i][j] == '1') ? 0xFFFFFF : 0x000000; // Wall is white, empty is black
            
            for (int y = 0; y < mini_tile_size; y++) {
                for (int x = 0; x < mini_tile_size; x++) {
                    put_pixel(player, MINIMAP_X + j * mini_tile_size + x, MINIMAP_Y + i * mini_tile_size + y, color);
                }
            }
        }
    }

    // Draw the player on the minimap
    int player_minimap_x = MINIMAP_X + (player->x / TILE_SIZE) * mini_tile_size + mini_tile_size / 2;
    int player_minimap_y = MINIMAP_Y + (player->y / TILE_SIZE) * mini_tile_size + mini_tile_size / 2;

    // Draw player position (as a small circle or cross)
    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            if (x * x + y * y <= 4) { // Simple circle radius
                put_pixel(player, player_minimap_x + x, player_minimap_y + y, 0xFF0000); // Red color for player
            }
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
    p.map_width = strlen(p.map[0]); // Assuming the first row determines width
    p.map_height = 0; // Initialize height to zero
    while (p.map[p.map_height]) { // Count rows for height
        p.map_height++;
    }
    p.mlx = mlx_init();
    if (!p.mlx) {
        printf("Erreur: Échec de l'initialisation de MiniLibX\n");
        return 1;
    }
    init_textures(&p);
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!p.window)
        return (1);
    p.img = mlx_new_image(p.mlx, SW, SH);
    p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
    clear_image(&p);
    draw_map(&p);
    draw_player(&p);
    cast_all_rays(&p);
    draw_minimap(&p);
    mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
    mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
    mlx_hook(p.window, 17, 0, close_window, &p);
    mlx_loop(p.mlx);
    return (0);
}
