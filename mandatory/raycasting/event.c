/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/16 17:38:22 by kahmada          ###   ########.fr       */
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

void	rotate_player(int keycode, t_player *player)
{
	double	rotationstep;

	rotationstep = player->rotationspeed;
	if (keycode == 123 || keycode == 0)
		player->rotationangle -= rotationstep;
	else if (keycode == 124 || keycode == 2)
		player->rotationangle += rotationstep;
}

void	move_player(int keycode, t_player *player)
{
	double	new_x;
	double	new_y;
	double	movestep;

	new_x = player->x;
	new_y = player->y;
	movestep = player->movespeed;
	if (keycode == 126 || keycode == 13)
	{
		new_x += cos(player->rotationangle) * movestep;
		new_y += sin(player->rotationangle) * movestep;
	}
	else if (keycode == 125 || keycode == 1)
	{
		new_x -= cos(player->rotationangle) * movestep;
		new_y -= sin(player->rotationangle) * movestep;
	}
	if (!is_wall(new_x, new_y, player))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

int	key_eshap(int keycode, t_player *player)
{
	rotate_player(keycode, player);
	move_player(keycode, player);
	if (keycode == 53)
		return(close_window(player));
	cast_all_rays(player);
	mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
	return (0);
}
