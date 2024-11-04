/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:41:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 21:20:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	is_wall(double x, double y, t_player *p)
{
	int	mapX;
	int	mapY;
	if (x < 0 || x > SW || y < 0 || y > SH) {
        return 1;
    }
	mapX = floor(x / TILE_SIZE);
	mapY = floor(y / TILE_SIZE);
	if (mapY < 0 || mapY >= MAP_NUM_ROWS || mapX < 0 \
	|| mapX >= MAP_NUM_COLS || p->map == NULL \
	|| p->map[mapY] == NULL || mapX >= ft_strlen(p->map[mapY])) 
		return (1);
	return (p->map[mapY][mapX] != '0');
}

void	cast_all_rays(t_player *player)
{
	double	ray_angle;
	int		i;

	clear_screen(player);
	draw_floor_and_ceiling(player);
	ray_angle = player->rotationAngle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		player->rays[i].angle = normalize_angle(ray_angle);
		cast_ray(player, &player->rays[i]);
		render_3d_wall_slice(player, i, player->rays[i].distance);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}
