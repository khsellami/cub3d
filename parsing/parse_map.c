/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:46:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 11:52:43 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int parse_map(t_game *game, char *map_file)
{
    (void)game;
    int fd;
    char *line = NULL;
    // int map_start = 0;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (0); // Erreur d'ouverture de fichier

    // Lire le fichier ligne par ligne
    while (get_next_line(fd) > 0)
    {
        // Vérifier si la ligne concerne une texture (NO, SO, WE, EA)
        // if (is_texture_line(line))
        //     parse_texture(game, line);
        // // Vérifier si la ligne concerne les couleurs (F pour le sol, C pour le plafond)
        // else if (is_color_line(line))
        //     parse_color(game, line);
        // // Si la ligne contient la map (1, 0, N, S, E, W)
        // else if (is_map_line(line))
        //     add_line_to_map(game, line, map_start++);
        // else
        //     return (ft_putstr_fd("Invalid map format\n", 2), 0); // Gestion des erreurs si le format est incorrect
        printf("[%s]\n", line);
        free(line);
    }
    close(fd);
    return (1);
}
