/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:22:22 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/19 18:18:17 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
#define CUB3D

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_game
{
    void    *mlx;
    void    *window;
    int     width;
    int     height;
    char    **map;
    double  player_x;
    double  player_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;

    
} t_game;



#endif