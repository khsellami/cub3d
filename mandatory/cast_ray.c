/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:40 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/05 16:14:33 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	horizontal_ray_intersection(t_player *player, t_ray *ray)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	int isRayFacingDown = ray->angle > 0 && ray->angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;

	yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;
	
	xintercept = player->x + (yintercept - player->y) / tan(ray->angle);
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;
	xstep = TILE_SIZE / tan(ray->angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;
	while (nextHorzTouchX >= 0 && nextHorzTouchX < SW && nextHorzTouchY >= 0 && nextHorzTouchY < SH)
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (!(ray->angle > 0 && ray->angle < M_PI) ? -1 : 0);
		if (is_wall(xToCheck, yToCheck, player))
		{
			ray->horizontal_distance = sqrt((nextHorzTouchX - player->x) * (nextHorzTouchX - player->x) \
			+ (nextHorzTouchY - player->y) * (nextHorzTouchY - player->y));
			ray->horz_x = nextHorzTouchX;
			ray->horz_y = nextHorzTouchY;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;	
		}
	}
}

void	vertical_ray_intersection(t_player *player, t_ray *ray)
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int isRayFacingDown = ray->angle > 0 && ray->angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;

    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;
	
	yintercept = player->y + (xintercept - player->x) * tan(ray->angle);

	xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;
	ystep = TILE_SIZE * tan(ray->angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
	
	double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;
	while (nextVertTouchX >= 0 && nextVertTouchX < SW && nextVertTouchY >= 0 && nextVertTouchY < SH)
	{
		double xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        double yToCheck = nextVertTouchY;
		if (is_wall(xToCheck, yToCheck, player))
		{
			ray->vertical_distance = sqrt((nextVertTouchX - player->x) * (nextVertTouchX - player->x) + \
			(nextVertTouchY - player->y) * (nextVertTouchY - player->y));
			ray->vert_x = nextVertTouchX;
			ray->vert_y = nextVertTouchY;
			break;
		}
		else
		{
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
			
		}
	}
}

void	cast_ray(t_player *player, t_ray *ray)
{
	ray->horizontal_distance = FLT_MAX;
	ray->vertical_distance = FLT_MAX;
	horizontal_ray_intersection(player, ray);
	vertical_ray_intersection(player, ray);
	if (ray->horizontal_distance < ray->vertical_distance)
		ray->distance = ray->horizontal_distance;
	else
		ray->distance = ray->vertical_distance;
}


