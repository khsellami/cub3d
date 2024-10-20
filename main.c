/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 11:50:01 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac,char **av)
{
    t_game game;
    
    if (ac != 2)
        return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
    if (!valid_file_name(av[1]))//rase name file av[1] sous forme : "##.cub"(extension .cub)
        return (ft_putstr_fd("Invalid file name\n", 2), 1);
    // //av[1] howa map dialena
    if (!init_game(&game , av[1]))
        return (ft_putstr_fd("Error initializing the game\n", 2), 1);
    if (!parse_map(&game, av[1]))//hena radi nediro parsing map : 
    //verifier si la ligne concerne les couleurs(F,C)
    //verifier si la ligne concerne une texture (NO,So,..)
    //verifier data correct
    //Si la ligne contient map (1, 0, N, S, E, W) : add line to map
        return (0);
    // if(!valid_map())
    //     return (0);
    //hena radi haneliwe events
    //keyrelease
    //destroy
    //keyclick
    // //loop continue affichage window until event
    // mlx_loop_hook(game.mlx, render3d, &game);//fi had render3d radi ne9ado raycasting
    mlx_loop(game.mlx);
    return (0);
}