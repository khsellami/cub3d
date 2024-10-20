/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:22:34 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 11:28:53 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int init_game(t_game *game, char *map_file)
{
    (void)map_file;
    game->mlx = mlx_init();
    if (!game->mlx)
        return (0);
    game->width = 800;
    game->height = 600;
    game->window = mlx_new_window(game->mlx, game->width, game->height, "cub3D");
    if (!game->window)
        return (0);
    // Ici, on pourrait initialiser d'autres données : les textures et les variables de joueur
    // Par exemple : la position initiale du joueur, direction, etc.
    return (1); // Tout s'est bien passé
}
