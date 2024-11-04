/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 22:00:46 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	exit_game(t_player *player)
{
	int	i;

	if (player->map)
	{
		i = 0;
		while (player->map[i])
		{
			free(player->map[i]);
			i++;
		}
		free(player->map);
	}
	mlx_destroy_window(player->mlx, player->window);
	exit(0);
}

int	key_eshap(int keycode, t_player *player)
{
	double	new_x;
	double	new_y;
	double	moveStep;
	double	rotationStep;

	new_x = player->x;
	new_y = player->y;
	moveStep = player->moveSpeed;
	rotationStep = player->rotationSpeed;
	if (keycode == 123 || keycode == 0)
		player->rotationAngle -= rotationStep;
	else if (keycode == 124 || keycode == 2)
		player->rotationAngle += rotationStep;
	else if (keycode == 126 || keycode == 13)
	{
		new_x += cos(player->rotationAngle) * moveStep;
		new_y += sin(player->rotationAngle) * moveStep;
	}
	else if (keycode == 125 || keycode == 1)
	{
		new_x -= cos(player->rotationAngle) * moveStep;
		new_y -= sin(player->rotationAngle) * moveStep;
	}
	else if (keycode == 53)
		exit_game(player);
	if (!is_wall(new_x, new_y, player))
	{
		player->x = new_x;
		player->y = new_y;
	}
	clear_image(player);
	cast_all_rays(player);
	mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
	return (0);
}
