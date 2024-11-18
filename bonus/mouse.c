/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:01:04 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/18 16:23:50 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	mouse_motion(int x, int y, t_player *player)
{
	double	deltax;
	double	deltay;
	double	rotationspeed;

	deltax = x - player->last_mouse_x;
	deltay = y - player->last_mouse_y;
	rotationspeed = 25;
	player->rotationangle += deltax * rotationspeed;
	player->x += cos(player->rotationangle) * deltay * player->movespeed;
	player->y += sin(player->rotationangle) * deltay * player->movespeed;
	player->last_mouse_x = x;
	player->last_mouse_y = y;
	if (is_wall(player->x, player->y, player))
	{
		player->x -= cos(player->rotationangle) * deltay * player->movespeed;
		player->y -= sin(player->rotationangle) * deltay * player->movespeed;
	}
	return (0);
}
