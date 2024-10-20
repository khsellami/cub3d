/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:22:34 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 19:47:42 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    
    game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (!game->window)
        return (0);
    
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img)
        return (0);
    
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_px, &game->line_len, &game->endian);
    if (!game->addr)
    {
        mlx_destroy_window(game->mlx, game->window); // Clean up window if address retrieval fails
        return (0);
    }
    
    game->player.x = 100;
    game->player.y = 100;
    game->player.angle = 0;
    game->ray.ray_ngl = game->player.angle;
    game->ray.distance = 0;
    game->ray.flag = 0;
    game->w_map = 25;
    game->h_map = 9;

    return (1);
}

