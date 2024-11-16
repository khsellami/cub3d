/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:36:58 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/16 17:39:22 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
		dst = player->img_data + \
		(y * player->line_length + x * (player->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
