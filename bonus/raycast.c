/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:20:05 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/29 13:21:38 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
void horizontal_ray_intersection(t_player *player, t_ray *ray)
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;

    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += (sin(ray->angle) > 0) ? TILE_SIZE : 0;
    xintercept = player->x + (yintercept - player->y) / tan(ray->angle);
    
    ystep = TILE_SIZE * ((sin(ray->angle) > 0) ? 1 : -1);
    xstep = ystep / tan(ray->angle);
    
    while (xintercept >= 0 && xintercept < SW && yintercept >= 0 && yintercept < SH)
    {
        if (is_wall(xintercept, yintercept - (sin(ray->angle) > 0 ? 0 : 1), player))
        {
            ray->horizontal_distance = sqrt((xintercept - player->x) * (xintercept - player->x) +
                                             (yintercept - player->y) * (yintercept - player->y));
            break;
        }
        xintercept += xstep;
        yintercept += ystep;
    }
}

void vertical_ray_intersection(t_player *player, t_ray *ray)
{
    float vert_x;
    float vert_y;
    float vert_dx;
    float vert_dy;

    vert_x = floor(player->x / TILE_SIZE) * TILE_SIZE;
    vert_x += (cos(ray->angle) > 0) ? TILE_SIZE : 0;
    vert_y = player->y + (vert_x - player->x) / cos(ray->angle) * sin(ray->angle);
    
    vert_dx = TILE_SIZE * ((cos(ray->angle) > 0) ? 1 : -1);
    vert_dy = vert_dx * tan(ray->angle);
    
    while (vert_x >= 0 && vert_x < SW && vert_y >= 0 && vert_y < SH) {
        if (is_wall(vert_x - (cos(ray->angle) > 0 ? 0 : 1), vert_y, player)) {
            ray->vertical_distance = sqrt((vert_x - player->x) * (vert_x - player->x) +
                                          (vert_y - player->y) * (vert_y - player->y));
            break;
        }
        vert_x += vert_dx;
        vert_y += vert_dy;
    }
}

void cast_ray(t_player *player, t_ray *ray)
{
    ray->horizontal_distance = INT_MAX;
    ray->vertical_distance = INT_MAX;

    horizontal_ray_intersection(player, ray);
    vertical_ray_intersection(player, ray);

    ray->distance = fmin(ray->horizontal_distance, ray->vertical_distance);
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

void cast_all_rays(t_player *player)
{
    float ray_angle;

    clear_screen(player);
    draw_floor_and_ceiling(player);
    ray_angle = player->rotationAngle - (FOV_ANGLE / 2);
    for (int i = 0; i < NUM_RAYS; i++)
    {
        player->rays[i].angle = normalize_angle(ray_angle);
        cast_ray(player, &player->rays[i]);
        render_3d_wall_slice(player, i, player->rays[i].distance);
        ray_angle += FOV_ANGLE / NUM_RAYS;
    }
}
