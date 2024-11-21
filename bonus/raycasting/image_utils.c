/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:36:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/21 15:01:05 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	clear_screen(t_player *player)
{
	int	color;
	int	y;
	int	x;

	color = 0x000000;
	y = 0;
	while (y < SH)
	{
		x = 0;
		while (x < SW)
		{
			put_pixel(player, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_player *player, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SW && y >= 0 && y < SH)
	{
		dst = player->img->data + \
		(y * player->img->line_length + x * (player->img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

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
