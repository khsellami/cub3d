/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:28:18 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/29 13:22:00 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void draw_player(t_player *player)
{
    int color = 0x00FF00;
    int x_center = player->x;
    int y_center = player->y;
    t_data data;

    for (data.y = -player->radius; data.y <= player->radius; data.y++)
    {
        for (data.x = -player->radius; data.x <= player->radius; data.x++)
        {
            if (data.x * data.x + data.y * data.y <= player->radius * player->radius)
            {
                put_pixel(player, x_center + data.x, y_center + data.y, color);
            }
        }
    }
}

void draw_map(t_player *player)
{
    int color;
    int i = 0;
    t_data data;
    while (player->map[i])
    {
        int j = 0;
        while (player->map[i][j])
        {
            if (player->map[i][j] == '1')
                color = 0xFFFFFF;
            else
                color = 0x000000;
            data.y = i * TILE_SIZE;
            data.x = j * TILE_SIZE;
            data.y_offset = 0;
            while (data.y_offset < TILE_SIZE)
            {
                data.x_offset = 0;
                while (data.x_offset < TILE_SIZE)
                {
                    put_pixel(player, data.x + data.x_offset, data.y + data.y_offset, color);
                    data.x_offset++;
                }
                data.y_offset++;
            }
            j++;
        }
        i++;
    }
}


void draw_wall(t_player *p, int x, int wall_height, int texture_index)
{
    
    float wall_top = (SH / 2) - (wall_height / 2);
    float wall_bottom = (SH / 2) + (wall_height / 2);
    t_img *current_texture = NULL;
    t_data data;
    int color;
    if (texture_index == 0)
        current_texture = &p->no_img;
    else if (texture_index == 1)
        current_texture = &p->so_img;
    else if (texture_index == 2)
        current_texture = &p->ea_img;
    else if (texture_index == 3)
        current_texture = &p->we_img;
    if (!current_texture || !current_texture->img)
    {
        printf("Erreur: Texture non chargée\n");
        return;
    }
    for (data.y = wall_top; data.y < wall_bottom; data.y++)
    {
        if (data.y < 0 || data.y >= SH) continue;
        data.tex_y = (data.y - wall_top) * current_texture->height / wall_height;
        data.tex_x = x % current_texture->width;
        color = *(int *)(current_texture->data + 
                             (data.tex_y * current_texture->line_length + data.tex_x * (current_texture->bpp / 8)));
        put_pixel(p, x, data.y, color);
    }
}

void render_player(t_player *player)
{
    int player_x = (int)(player->x);
    int player_y = (int)(player->y);
    int radius;
    t_data data;

    radius = player->radius;
    data.y = -radius;;
    while (data.y <= radius)
    {
        data.x = -radius;
        while (data.x <= radius)
        {
            if (data.x * data.x + data.y * data.y <= radius * radius)
            {
                data.px = player_x + data.x;
                data.py = player_y + data.y;
                if (data.px >= 0 && data.px < SW && data.py >= 0 && data.py < SH)
                {
                    put_pixel(player, data.px, data.py, 0xFFFF00);
                }
            }
            data.x++;
        }
        data.y++;
    }
}


void draw_floor_and_ceiling(t_player *player)
{
    int y = 0;
    int x;
    while (y < SH / 2)
    {
        x = 0;
        while (x < SW)
        {
            put_pixel(player, x, y, player->ciel_color);
            x++;
        }
        y++;
    }
    y = SH / 2;
    while (y < SH)
    {
        x = 0;
        while (x < SW)
        {
            put_pixel(player, x, y, player->floor_color);
            x++;
        }
        y++;
    }
}
