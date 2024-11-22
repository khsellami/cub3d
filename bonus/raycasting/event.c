/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/22 12:58:43 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	calcul_nw_p(int keycode, t_player *player, double *new_x, double *new_y)
{
	double	movestep;

	movestep = player->movespeed + 3;
	if (keycode == 13)
	{
		*new_x += cos(player->rotationangle) * movestep;
		*new_y += sin(player->rotationangle) * movestep;
	}
	else if (keycode == 1)
	{
		*new_x -= cos(player->rotationangle) * movestep;
		*new_y -= sin(player->rotationangle) * movestep;
	}
	else if (keycode == 0)
	{
		*new_x += cos(player->rotationangle - M_PI_2) * movestep;
		*new_y += sin(player->rotationangle - M_PI_2) * movestep;
	}
	else if (keycode == 2)
	{
		*new_x += cos(player->rotationangle + M_PI_2) * movestep;
		*new_y += sin(player->rotationangle + M_PI_2) * movestep;
	}
}

void	move_player(int keycode, t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->x;
	new_y = player->y;
	calcul_nw_p(keycode, player, &new_x, &new_y);
	if (keycode == 123)
		player->rotationangle -= player->rotationspeed * 1.5;
	else if (keycode == 124)
		player->rotationangle += player->rotationspeed * 1.5;
	if (!is_wall(new_x, new_y, player) && wall_collisions(player, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

int	key_eshap(int keycode, t_player *player)
{
	move_player(keycode, player);
	if (keycode == 53)
		return (close_window(player));
	if (keycode == 12)
		player->is_animating = 1;
	else if (keycode == 14)
		player->is_animating = 0;
	clear_screen(player);
	cast_all_rays(player);
	draw_pistol(player);
	draw_map(player);
	mlx_put_image_to_window(player->mlx, player->window, \
	player->img->img, 0, 0);
	return (0);
}
