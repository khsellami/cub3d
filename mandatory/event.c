/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:19 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/01 16:13:47 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void exit_game(t_player *player)
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
}

int key_eshap(int keycode, t_player *player)
{
    float new_x = player->x;
    float new_y = player->y;
    float moveStep = player->moveSpeed;
    float rotationStep = player->rotationSpeed;

    if (keycode == 123 || keycode == 0)
        player->rotationAngle -= rotationStep;
    else if (keycode == 124 || keycode == 2)
        player->rotationAngle += rotationStep;
    else if (keycode == 126 || keycode == 13)
    {
        new_x += cos(player->rotationAngle) * moveStep;
        new_y += sin(player->rotationAngle) * moveStep;
    }
    else if (keycode == 125 || keycode == 1)
    {
        new_x -= cos(player->rotationAngle) * moveStep;
        new_y -= sin(player->rotationAngle) * moveStep;
    }
    else if (keycode == 53)
    {
        exit_game(player);
    }
    if (!is_wall(new_x, new_y, player))
    {
        player->x = new_x;
        player->y = new_y;
    }
    clear_image(player);
    draw_map(player);
    draw_player(player);
    cast_all_rays(player);
    mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
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
