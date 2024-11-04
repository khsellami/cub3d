/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:20:05 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/04 16:14:20 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void horizontal_ray_intersection(t_player *player, t_ray *ray)
{
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;

    // Initialisation de xintercept et yintercept
    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += (sin(ray->angle) > 0) ? TILE_SIZE : 0;
    xintercept = player->x + (yintercept - player->y) / tan(ray->angle);
    
    // Calcul des steps pour traverser la grille
    ystep = TILE_SIZE * ((sin(ray->angle) > 0) ? 1 : -1);
    xstep = ystep / tan(ray->angle);
    
    while (xintercept >= 0 && xintercept < SW && yintercept >= 0 && yintercept < SH) {
        // Vérification de collision avec un mur
        if (is_wall(xintercept, yintercept - (sin(ray->angle) > 0 ? 0 : 1), player)) {
            ray->horizontal_distance = sqrt((xintercept - player->x) * (xintercept - player->x) +
                                             (yintercept - player->y) * (yintercept - player->y));
            ray->horz_x = xintercept;
            ray->horz_y = yintercept;
            break;
        }
        xintercept += xstep;
        yintercept += ystep;
    }
}



void vertical_ray_intersection(t_player *player, t_ray *ray)
{
    double vert_x;
    double vert_y;
    double vert_dx;
   double vert_dy;

    // Initialisation de vert_x et vert_y
    vert_x = floor(player->x / TILE_SIZE) * TILE_SIZE;
    vert_x += (cos(ray->angle) > 0) ? TILE_SIZE : 0;
    vert_y = player->y + (vert_x - player->x) * tan(ray->angle);
    
    // Calcul des steps pour traverser la grille
    vert_dx = TILE_SIZE * ((cos(ray->angle) > 0) ? 1 : -1);
    vert_dy = vert_dx * tan(ray->angle);
    
    while (vert_x >= 0 && vert_x < SW && vert_y >= 0 && vert_y < SH) {
        // Vérification de collision avec un mur
        if (is_wall(vert_x - (cos(ray->angle) > 0 ? 0 : 1), vert_y, player)) {
            ray->vertical_distance = sqrt((vert_x - player->x) * (vert_x - player->x) +
                                          (vert_y - player->y) * (vert_y - player->y));
            ray->vert_x = vert_x;
            ray->vert_y = vert_y;
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

    // Correction de la distance pour l'angle
    ray->distance = fmin(ray->horizontal_distance, ray->vertical_distance);
    
    // ray->distance *= cos(ray->angle - player->rotationAngle);  // Correction de la perspective
}


double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}

void cast_all_rays(t_player *player)
{
    double ray_angle;

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

void calculate_wall_properties(t_player *player, int ray_id, double distance, t_data *data)
{
    data->angle_diff = player->rays[ray_id].angle - player->rotationAngle;
    data->corrected_distance = distance * cos(data->angle_diff);
    if (data->corrected_distance <= 0)
    {
        data->wall_height = 40;
        // return;
    }
    double proj = (SW / 2) / tan(FOV_ANGLE / 2);
    data->wall_height = (TILE_SIZE / data->corrected_distance) * proj;
    data->wall_top = (SH / 2) - (data->wall_height / 2);
    data->wall_bottom = (SH / 2) + (data->wall_height / 2);
    if (data->wall_bottom >= SH) 
        data->wall_bottom = SH - 1;
    data->x_pos = ray_id;
}

t_img *get_texture(t_player *player, int ray_id)
{
    int texture_index;

    if (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance)
    {
        if (cos(player->rays[ray_id].angle) > 0)
            texture_index = 2;
        else
            texture_index = 3;
    }
    else
    {
        if (sin(player->rays[ray_id].angle) > 0)
            texture_index = 0;
        else
            texture_index = 1;
    }
    if (texture_index == 0)
        return &player->no_img;
    else if (texture_index == 1)
        return &player->so_img;
    else if (texture_index == 2)
        return &player->ea_img;
    else 
        return &player->we_img;
}


int calculate_texture_x(t_player *player, int ray_id, t_img *texture)
{
    double wall_hit;

    if (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance) {
        wall_hit = fmod(player->rays[ray_id].vert_y, TILE_SIZE);
    } else {
        wall_hit = fmod(player->rays[ray_id].horz_x, TILE_SIZE);
    }

    return (int)(wall_hit * texture->width / TILE_SIZE);
}

void render_wall_slice(t_player *player, t_data *data, t_img *texture)
{
    int color, d, y;
    if (data->wall_height <= 0) {
        printf("Erreur: wall_height %d est invalide\n", data->wall_height);
        return;
        data->wall_height = 10;
    }
    if (texture->height <= 0) {
        printf("Erreur: texture height %d est invalide\n", texture->height);
        return;
    }
    for (y = data->wall_top; y <= data->wall_bottom; y++)
    {
        d = (y - data->wall_top) * texture->height / data->wall_height;
        data->texture_y = abs(d % texture->height);
        if (data->texture_y < 0 || data->texture_y >= texture->height)
        {
            printf("Erreur: texture_y %d est hors limites\n", data->texture_y);
            return;
        }
        if (data->texture_x < 0 || data->texture_x >= texture->width)
        {
            printf("Erreur: texture_x %d est hors limites\n", data->texture_x);
            return;
        }
        color = *(int *)(texture->data + (data->texture_y * texture->line_length + data->texture_x * (texture->bpp / 8)));
        if (color == 0)
            color = 0x00FF00;
        put_pixel(player, data->x_pos, y, color);
    }
}


void render_3d_wall_slice(t_player *player, int ray_id, double distance)
{
    t_data data;
    t_img *texture;

    calculate_wall_properties(player, ray_id, distance, &data);
    texture = get_texture(player, ray_id);
    if (!texture || !texture->img)
    {
        printf("Erreur: La texture %d n'est pas chargée correctement\n", data.texture_index);
        return;
    }
    data.texture_x = calculate_texture_x(player, ray_id, texture);
    if (data.texture_x < 0 || data.texture_x >= texture->width)
    {
        printf("Erreur: texture_x %d est hors limites\n", data.texture_x);
        return;
    }
    render_wall_slice(player, &data, texture);
}
