/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:25:38 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 17:29:26 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void put_pixel(t_player *player, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < SW && y >= 0 && y < SH)
    {
        dst = player->img_data + (y * player->line_length + x * (player->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

// void calculate_wall_properties(t_player *player, int ray_id,  distance, t_data *data)
// {
//     data->angle_diff = player->rays[ray_id].angle - player->rotationAngle;
//     data->corrected_distance = distance * cos(data->angle_diff);
//     data->wall_height = (TILE_SIZE * SH) / data->corrected_distance;
//     data->wall_top = (SH / 2) - (data->wall_height / 2);
//     if (data->wall_top < 0) data->wall_top = 0;
//     data->wall_bottom = (SH / 2) + (data->wall_height / 2);
//     if (data->wall_bottom >= SH) data->wall_bottom = SH - 1;
//     data->x_pos = (ray_id * SW) / NUM_RAYS;
// }

// t_img *get_texture(t_player *player, int ray_id)
// {
//     int texture_index;

//     if (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance)
//     {
//         if (cos(player->rays[ray_id].angle) > 0)
//             texture_index = 2;
//         else
//             texture_index = 3;
//     }
//     else
//     {
//         if (sin(player->rays[ray_id].angle) > 0)
//             texture_index = 0;
//         else
//             texture_index = 1;
//     }
//     if (texture_index == 0)
//         return &player->no_img;
//     else if (texture_index == 1)
//         return &player->so_img;
//     else if (texture_index == 2)
//         return &player->ea_img;
//     else 
//         return &player->we_img;
// }


// int calculate_texture_x(t_player *player, int ray_id, t_img *texture)
// {
//     return (int)(fmod(player->rays[ray_id].distance, TILE_SIZE) * texture->width / TILE_SIZE);
// }

// void render_wall_slice(t_player *player, t_data *data, t_img *texture)
// {
//     int color, d, y;

//     for (y = data->wall_top; y <= data->wall_bottom; y++)
//     {
//         d = (y - data->wall_top) * texture->height / data->wall_height;
//         data->texture_y = d % texture->height;
//         if (data->texture_y < 0 || data->texture_y >= texture->height)
//         {
//             printf("Erreur: texture_y %d est hors limites\n", data->texture_y);
//             return;
//         }
//         color = *(int *)(texture->data + (data->texture_y * texture->line_length + data->texture_x * (texture->bpp / 8)));
//         if (color == 0) color = 0x00FF00;
//         put_pixel(player, data->x_pos, y, color);
//     }
// }

// void render_3d_wall_slice(t_player *player, int ray_id, float distance)
// {
//     t_data data;
//     t_img *texture;

//     calculate_wall_properties(player, ray_id, distance, &data);
//     texture = get_texture(player, ray_id);
//     if (!texture || !texture->img)
//     {
//         printf("Erreur: La texture %d n'est pas chargée correctement\n", data.texture_index);
//         return;
//     }
//     data.texture_x = calculate_texture_x(player, ray_id, texture);
//     if (data.texture_x < 0 || data.texture_x >= texture->width)
//     {
//         printf("Erreur: texture_x %d est hors limites\n", data.texture_x);
//         return;
//     }
//     render_wall_slice(player, &data, texture);
// }
