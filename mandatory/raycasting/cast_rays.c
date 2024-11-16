/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:41:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/16 17:33:56 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	ft_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	determine_ray_facing_direction(t_ray *ray)
{
	ray->israyfacingdown = ray->angle > 0 && ray->angle < M_PI;
	ray->israyfacingup = !(ray->israyfacingdown);
	ray->israyfacingright = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
	ray->israyfacingleft = !(ray->israyfacingright);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	is_wall(double x, double y, t_player *p)
{
	int	mapx;
	int	mapy;

	if (x < 0 || x > SW || y < 0 || y > SH)
		return (1);
	mapx = floor(x / TILE_SIZE);
	mapy = floor(y / TILE_SIZE);
	if (mapy < 0 || mapy >= p->map_row || mapx < 0 \
	|| mapx >= p->map_col || p->map == NULL \
	|| p->map[mapy] == NULL || mapx >= ft_strlen(p->map[mapy]))
		return (1);
	return (p->map[mapy][mapx] != '0');
}

void	cast_all_rays(t_player *player)
{
	double	ray_angle;
	int		i;

	draw_floor_and_ceiling(player);
	ray_angle = player->rotationangle - (FOV_ANGLE / 2);
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
