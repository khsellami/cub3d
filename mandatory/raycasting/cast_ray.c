/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:40 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/18 15:53:04 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	find_horizontal_intersection(t_player *player, t_ray *ray, \
double xstep, double ystep)
{
	double	nexthx;
	double	nexthy;
	double	xtocheck;
	double	ytocheck;

	nexthx = ray->xintercept;
	nexthy = ray->yintercept;
	while (nexthx >= 0 && nexthx < SW && nexthy >= 0 && nexthy < SH)
	{
		xtocheck = nexthx;
		if (ray->israyfacingup)
			ytocheck = nexthy - 1;
		else
			ytocheck = nexthy;
		if (is_wall(xtocheck, ytocheck, player))
		{
			ray->horizontal_distance = ft_dist(player->x, \
			player->y, nexthx, nexthy);
			ray->horz_x = nexthx;
			ray->horz_y = nexthy;
			break ;
		}
		nexthx += xstep;
		nexthy += ystep;
	}
}

void	horizontal_ray_intersection(t_player *player, t_ray *ray)
{
	double	xstep;
	double	ystep;

	determine_ray_facing_direction(ray);
	ray->yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (ray->israyfacingdown)
		ray->yintercept += TILE_SIZE;
	ray->xintercept = player->x + \
	(ray->yintercept - player->y) / tan(ray->angle);
	ystep = TILE_SIZE;
	if (ray->israyfacingup)
		ystep *= -1;
	xstep = TILE_SIZE / tan(ray->angle);
	if (ray->israyfacingleft && xstep > 0)
		xstep *= -1;
	else if (ray->israyfacingright && xstep < 0)
		xstep *= -1;
	find_horizontal_intersection(player, ray, xstep, ystep);
}

void	find_vertical_intersection(t_player *player, t_ray *ray, \
double xstep, double ystep)
{
	double	nextvx;
	double	nextvy;
	double	xtocheck;
	double	ytocheck;

	nextvx = ray->xintercept;
	nextvy = ray->yintercept;
	while (nextvx >= 0 && nextvx < SW && nextvy >= 0 && nextvy < SH)
	{
		if (ray->israyfacingleft)
			xtocheck = nextvx - 1;
		else
			xtocheck = nextvx;
		ytocheck = nextvy;
		if (is_wall(xtocheck, ytocheck, player))
		{
			ray->vertical_distance = ft_dist(player->x, player->y, \
			nextvx, nextvy);
			ray->vert_x = nextvx;
			ray->vert_y = nextvy;
			break ;
		}
		nextvx += xstep;
		nextvy += ystep;
	}
}

void	vertical_ray_intersection(t_player *player, t_ray *ray)
{
	double	xstep;
	double	ystep;

	determine_ray_facing_direction(ray);
	ray->xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->israyfacingright)
		ray->xintercept += TILE_SIZE;
	ray->yintercept = player->y + \
	(ray->xintercept - player->x) * tan(ray->angle);
	xstep = TILE_SIZE;
	if (ray->israyfacingleft)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray->angle);
	if (ray->israyfacingup && ystep > 0)
		ystep *= -1;
	else if (ray->israyfacingdown && ystep < 0)
		ystep *= -1;
	find_vertical_intersection(player, ray, xstep, ystep);
}

void	cast_ray(t_player *player, t_ray *ray)
{
	ray->horizontal_distance = INT_MAX;
	ray->vertical_distance = INT_MAX;
	horizontal_ray_intersection(player, ray);
	vertical_ray_intersection(player, ray);
	if (ray->horizontal_distance < ray->vertical_distance)
		ray->distance = ray->horizontal_distance;
	else
		ray->distance = ray->vertical_distance;
}
