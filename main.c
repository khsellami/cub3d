/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/19 18:28:34 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int parse_map(t_game *game, char *map_file)
{
    int fd;
    char *line;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (0); // Erreur d'ouverture de fichier
    while (get_next_line(fd, &line))
    {
        // Vérifiez si la ligne concerne une texture (NO, SO, etc.)
        if (is_texture_line(line))
            parse_texture(game, line);
        // Vérifiez si la ligne concerne les couleurs (F, C)
        else if (is_color_line(line))
            parse_color(game, line);
        // Si la ligne contient la carte (1, 0, N, S, E, W)
        else if (is_map_line(line))
            add_line_to_map(game, line);
        free(line);
    }
    close(fd);
    return (1);
}


int init_game(t_game *game, char *map_file)
{
    //hena initialisation dial struct dialena
    game->mlx = mlx_init();
    game->width = 800;
    game->height = 600;
    game->window = mlx_new_window(game->mlx, game->width, game->height, "cub3D");
    if (!game->window)
        return (0);
    // if (!parse_map(game, map_file))//hena radi nediro parsing map
    //     return (0);
    //hena radi haneliwe events
    // mlx_key_hook(game->window, handle_key, game);
    // mlx_loop_hook(game->mlx, render, game);
    return (1);
}


int main(int ac,char **av)
{
    t_game game;
    
    if (ac != 2)
    {
        write(2,"Usage: ./cub3D <map.cub>\n", 26);
        return (1);
    }
    //av[1] howa map dialena
    if (!init_game(&game , av[1]))
    {
        write(2, "Error initializing the game\n", 29);
        return (1);
    }
    //loop continue affichage window until event
    mlx_loop(game.mlx);
    return (0);
}