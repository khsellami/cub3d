/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/29 11:20:30 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_data(t_player *p)
{
    int i;

    i = 0;
    p->x = SW / 2;
    p->y = SH / 2;
    p->angle = 0;
    p->radius = 3;
    p->rotationAngle = M_PI / 2;
    p->moveSpeed = 2.0;
    p->rotationSpeed = 2 * (M_PI / 180);
    p->mlx = NULL;
    p->window = NULL;
    p->img = NULL;
    p->img_data = NULL;
    p->bpp = 0;
    p->line_length = 0;
    p->endian = 0;
    p->no = NULL;
    p->so = NULL;
    p->ea = NULL;
    p->we = NULL;
    p->floor_color = 0x8B4513;  // Erde (Braun)
    p->ciel_color = 0x87CEEB;   // Himmel (Hellblau)

    p->map = NULL;
    while (i < NUM_RAYS)
    {
        p->rays[i].horizontal_distance = 0;
        p->rays[i].vertical_distance = 0;
        p->rays[i].distance = 0.0;
        p->rays[i].angle = 0.0;
        i++;
    }
}