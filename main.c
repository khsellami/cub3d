/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 18:40:43 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int key_press(int keycode, t_game *game)
// {
//     if (keycode == KEY_W) // Move forward
//     {
//         game->player.x += cos(game->player.angle) * speed;
//         game->player.y += sin(game->player.angle) * speed;
//     }
//     else if (keycode == KEY_S) // Move backward
//     {
//         game->player.x -= cos(game->player.angle) * speed;
//         game->player.y -= sin(game->player.angle) * speed;
//     }
//     else if (keycode == KEY_A) // Turn left
//     {
//         game->player.angle -= 0.1; // Adjust the angle as needed
//     }
//     else if (keycode == KEY_D) // Turn right
//     {
//         game->player.angle += 0.1; // Adjust the angle as needed
//     }
//     else if (keycode == KEY_ESC) // Escape to exit
//     {
//         exit(0); // Exit the game
//     }
    
//     return 0; // Return as required
// }

int main(int ac,char **av)
{
    t_game game;
    
    if (ac != 2)
        return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
    //extension ".cub"
    if (!valid_file_name(av[1]))
        return (ft_putstr_fd("Invalid file name\n", 2), 1);
    //Initialisation game and player
    if (!init_game(&game))
        return (ft_putstr_fd("Error initializing the game\n", 2), 1);
    /// Remplissage map
    if (!parse_map(&game, av[1]))
        return (0);
    if(!valid_map(&game))
        return (ft_putstr_fd("Invalid map\n", 2), 0);
    //Events
    //keyrelease
    //destroy
    //keyclick
    // mlx_key_hook(game.mlx, &mlx_key, &game);	// key press and release
    // mlx_hook(game.window, KeyPress, KeyPressMask, key_press, &game); // Handle key presses
    // mlx_hook(game.window, DestroyNotify, NoEventMask, close_game, &game); // Handle window close
    //Raycasting
    mlx_loop_hook(game.mlx, render3d, &game);
    mlx_loop(game.mlx);
    return (0);
}