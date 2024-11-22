/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/22 12:45:54 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	close_window(t_player *player)
{
	int	i;

	i = 0;
	if (player->map)
	{
		while (player->map[i])
		{
			free(player->map[i]);
			i++;
		}
		free(player->map);
	}
	mlx_destroy_window(player->mlx, player->window);
	exit(0);
	return (0);
}

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
	if (!is_wall(new_x, new_y, player))
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
	clear_screen(player);
	cast_all_rays(player);
	mlx_put_image_to_window(player->mlx, player->window, \
	player->img->img, 0, 0);
	return (0);
}
