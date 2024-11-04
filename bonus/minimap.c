/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:34:13 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 21:43:29 by kahmada          ###   ########.fr       */
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

void draw_minimap(t_player *player)
{
    int color;
    int i = 0;
    int mini_map_scale = MINI_MAP_SIZE / player->map_width; // Scale for minimap

    // Clear the minimap background (black)
    fill_rectangle(player->img_data, MINI_MAP_X, MINI_MAP_Y, MINI_MAP_SIZE, MINI_MAP_SIZE, 0x000000);

    while (player->map[i])
    {
        int j = 0;
        while (player->map[i][j])
        {
            // Set color based on map data
            if (player->map[i][j] == '1') // Wall
                color = 0xFFFFFF; // White for walls
            else
                color = 0x000000; // Black for empty spaces

            // Calculate position on the minimap
            int mini_map_x = MINI_MAP_X + (j * mini_map_scale);
            int mini_map_y = MINI_MAP_Y + (i * mini_map_scale);

            // Fill the tile on the minimap
            for (int y_offset = 0; y_offset < mini_map_scale; y_offset++)
            {
                for (int x_offset = 0; x_offset < mini_map_scale; x_offset++)
                {
                    put_pixel(player, mini_map_x + x_offset, mini_map_y + y_offset, color);
                }
            }
            j++;
        }
        i++;
    }

    // Draw the player on the minimap
    double player_x = MINI_MAP_X + (player->pos_x * mini_map_scale);
    double player_y = MINI_MAP_Y + (player->pos_y * mini_map_scale);
    fill_circle(player->img_data, player_x, player_y, mini_map_scale / 4, 0xFF0000); // Draw player in red
}

