/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:58:14 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/09 22:00:47 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_player(t_player *player)
{
	int		color;
	int		x_center;
	int		y_center;
	t_data	data;

	color = 0x00FF00;
	x_center = player->x / 5;
	y_center = player->y / 5;
	data.y = -player->radius;
	while (data.y <= player->radius)
	{
		data.x = -player->radius;
		while (data.x <= player->radius)
		{
			if (data.x * data.x + data.y * data.y \
			<= player->radius * player->radius)
				put_pixel(player, x_center + data.x, y_center + data.y, color);
			data.x++;
		}
		data.y++;
	}
}

void	draw_tile(t_player *player, int i, int j, char tile)
{
	t_data	data;
	int		color;

	if (tile == '1')
		color = 0xFFFFFF;
	else
		color = 0x000000;
	data.y = i * TILE_SIZE / 5;
	data.x = j * TILE_SIZE / 5;
	data.y_offset = 0;
	while (data.y_offset < TILE_SIZE)
	{
		data.x_offset = 0;
		while (data.x_offset < TILE_SIZE)
		{
			put_pixel(player, data.x + \
			data.x_offset, data.y + data.y_offset, color);
			data.x_offset++;
		}
		data.y_offset++;
	}
}

void	draw_map(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (player->map[i])
	{
		j = 0;
		while (player->map[i][j])
		{
			draw_tile(player, i, j, player->map[i][j]);
			j++;
		}
		i++;
	}
	draw_player(player);
}
