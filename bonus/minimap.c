/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:34:13 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 17:45:05 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
void fill_rectangle(char *img_data, int x, int y, int width, int height, int color)
{
    int i, j;
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            int pixel_index = (y + j) * (SW * 4) + (x + i) * 4; // Assuming 32-bit color
            if (pixel_index >= 0 && pixel_index < SW * SH * 4) // Prevent out of bounds
            {
                img_data[pixel_index] = (color & 0xFF); // Blue
                img_data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
                img_data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
            }
        }
    }
}

void fill_circle(char *img_data, int center_x, int center_y, int radius, int color)
{
    int x, y;
    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius) // Check if the point is inside the circle
            {
                int pixel_index = (center_y + y) * (SW * 4) + (center_x + x) * 4; // Assuming 32-bit color
                if (pixel_index >= 0 && pixel_index < SW * SH * 4) // Prevent out of bounds
                {
                    img_data[pixel_index] = (color & 0xFF); // Blue
                    img_data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
                    img_data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
                }
            }
        }
    }
}

void draw_mini_map(t_player *player)
{
    int x, y;
    int map_x, map_y;
    int mini_map_scale = MINI_MAP_SIZE / player->map_width; // Adjust based on your map size
    double player_x, player_y;

    // Draw the mini-map background
    fill_rectangle(player->img_data, MINI_MAP_X, MINI_MAP_Y, MINI_MAP_SIZE, MINI_MAP_SIZE, 0x000000); // Black background

    // Draw the map
    for (y = 0; y < player->map_height; y++)
    {
        for (x = 0; x < player->map_width; x++)
        {
            if (player->map[y][x] == '1') // Assuming '1' represents walls
            {
                // Calculate mini-map position
                map_x = MINI_MAP_X + (x * mini_map_scale);
                map_y = MINI_MAP_Y + (y * mini_map_scale);
                fill_rectangle(player->img_data, map_x, map_y, mini_map_scale, mini_map_scale, 0xFFFFFF); // White wall
            }
        }
    }

    // Draw the player on the mini-map
    player_x = MINI_MAP_X + (player->pos_x * mini_map_scale);
    player_y = MINI_MAP_Y + (player->pos_y * mini_map_scale);
    fill_circle(player->img_data, player_x, player_y, mini_map_scale / 4, 0xFF0000); // Red player
}
