/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkValidMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:42:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:45:11 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int valid_map(t_game *game)
{
    // Implement your validation logic here
    // Example checks could include:
    
    // Check if there's at least one starting position
    int has_starting_position = 0;
    for (int i = 0; game->map[i] != NULL; i++) {
        if (ft_strchr(game->map[i], 'N') || 
            ft_strchr(game->map[i], 'S') || 
            ft_strchr(game->map[i], 'E') || 
            ft_strchr(game->map[i], 'W')) {
            has_starting_position = 1;
            break;
        }
    }
    
    if (!has_starting_position) {
        printf("Error: No starting position found in the map.\n");
        return 0; // Invalid map
    }

    // Additional validation checks...
    
    return 1; // Map is valid
}
