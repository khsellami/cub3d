/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/10 20:20:52 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	wall_collisions(t_player *data,int i, int j)
{
	int	x;
	int	y;

	x = (int)floor(j / TILE_SIZE);
	y = (int)floor(i / TILE_SIZE);
	if (data->map[x][(int)floor(data->x / TILE_SIZE)] == '1' && \
	data->map[(int)floor(data->y / TILE_SIZE)][y] == '1')
		return (0);
	return (1);
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

void	handle_player_rotation_and_animation(int keycode, t_player *player)
{
	double	rotationstep;

	rotationstep = player->rotationspeed;
	if (keycode == 12)
		player->is_animating = 1;
	else if (keycode == 14)
		player->is_animating = 0;
	else if (keycode == 123)
	{
		player->rotationangle -= rotationstep;
		if (player->rotationangle < 0)
			player->rotationangle += 2 * M_PI;
	}
	else if (keycode == 124)
	{
		player->rotationangle += rotationstep;
		if (player->rotationangle >= 2 * M_PI)
			player->rotationangle -= 2 * M_PI;
	}
}

void	handle_player_movement(int keycode, t_player *player)
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
	if (!is_wall(new_x, new_y, player)  && wall_collisions(player, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_player(int keycode, t_player *player)
{
	handle_player_rotation_and_animation(keycode, player);
	handle_player_movement(keycode, player);
}

int	key_eshap(int keycode, t_player *player)
{
	rotate_player(keycode, player);
	move_player(keycode, player);
	if (keycode == 53)
		exit_game(player);
	clear_image(player);
	cast_all_rays(player);
	draw_pistol(player);
	draw_map(player);
	mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
	return (0);
}
