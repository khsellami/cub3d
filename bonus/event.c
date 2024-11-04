/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:19 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/04 10:45:02 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
    double new_x = player->x;
    double new_y = player->y;
    double moveStep = player->moveSpeed;
    double rotationStep = player->rotationSpeed;

    // Gestion des rotations
    if (keycode == 123) // Rotation à gauche
    {
        player->rotationAngle -= rotationStep;
        if (player->rotationAngle < 0) // Normalisation de l'angle
            player->rotationAngle += 2 * M_PI;
    }
    else if (keycode == 124 || keycode == 124) // Rotation à droite
    {
        player->rotationAngle += rotationStep;
        if (player->rotationAngle >= 2 * M_PI) // Normalisation de l'angle
            player->rotationAngle -= 2 * M_PI;
    }
    if (keycode == 126 || keycode == 13) // Avancer
    {
        new_x += cos(player->rotationAngle) * moveStep;
        new_y += sin(player->rotationAngle) * moveStep;
    }
    else if (keycode == 125 || keycode == 1) // Reculer
    {
        new_x -= cos(player->rotationAngle) * moveStep;
        new_y -= sin(player->rotationAngle) * moveStep;
    }
    if (!is_wall(new_x, new_y, player))
    {
        player->x = new_x;
        player->y = new_y;
    }
    if (keycode == 53)
    {
        exit_game(player);
    }
    clear_image(player);
    draw_map(player);
    cast_all_rays(player);
    draw_minimap(player);
    draw_pistol(player);
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
