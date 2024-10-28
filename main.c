/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 12:27:05 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void clear_image(t_player *player)
{
    int img_size = SW * SH * 4;
    memset(player->img_data, 0, img_size);
}

void put_pixel(t_player *player, int x, int y, int color)
{
    if (x >= 0 && x < SW && y >= 0 && y < SH)
    {
        char *dst = player->img_data + (y * player->line_length + x * (player->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_player(t_player *player)
{
    int color = 0x00FF00;
    int x_center = player->x;
    int y_center = player->y;

    for (int y = -player->radius; y <= player->radius; y++)
    {
        for (int x = -player->radius; x <= player->radius; x++)
        {
            if (x * x + y * y <= player->radius * player->radius)
            {
                put_pixel(player, x_center + x, y_center + y, color);
            }
        }
    }
}

void draw_map(t_player *player) {
    for (int i = 0; player->map[i]; i++) {
        for (int j = 0; player->map[i][j]; j++) {
            int color = (player->map[i][j] == '1') ? 0xFFFFFF : 0x000000;
            for (int y = i * TILE_SIZE; y < (i + 1) * TILE_SIZE; y++) {
                for (int x = j * TILE_SIZE; x < (j + 1) * TILE_SIZE; x++) {
                    put_pixel(player, x, y, color);
                }
            }
        }
    }
}

int is_wall(float x, float y, t_player *p)
{
    int mapX = (int)(x / TILE_SIZE);
    int mapY = (int)(y / TILE_SIZE);

    // Check for out-of-bounds access
    if (mapY < 0 || mapY >= MAP_NUM_ROWS || mapX < 0 || mapX >= MAP_NUM_COLS || 
        p->map == NULL || p->map[mapY] == NULL || 
        mapX >= (int)strlen(p->map[mapY])) 
        return 1;

    // printf("is_wall: Checking at x=%f, y=%f -> mapX=[%d], mapY=[%d]\n", x, y, mapX, mapY);
    return (p->map[mapY][mapX] == '1');
}

void cast_ray(t_player *player, t_ray *ray)
{
    float ray_dx = cos(ray->angle);
    float ray_dy = sin(ray->angle);

    ray->horizontal_distance = INT_MAX;
    ray->vertical_distance = INT_MAX;
    // ****Horizontal RAY-GRID intersections****
    float xintercept, yintercept, xstep, ystep;
    //Find coordinate of the first horizontal intersection (point A)
    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += (ray_dy > 0) ? TILE_SIZE : 0;//ray f acing down : tile_size otherwise : 0
    xintercept = player->x + (yintercept - player->y) / tan(ray->angle);
    //Calculate increment for x-step and y-step
    ystep = TILE_SIZE * ((ray_dy > 0) ? 1 : -1);//this operator ternaire here manage where my ray is facing : facing up : *-1 , facing down : *1 
    xstep = ystep / tan(ray->angle);
    while (xintercept >= 0 && xintercept < SW && yintercept >= 0 && yintercept < SH)
    {
        if (is_wall(xintercept, yintercept - (ray_dy > 0 ? 0 : 1), player))
        {
            ray->horizontal_distance = sqrt((xintercept - player->x) * (xintercept - player->x) + (yintercept - player->y) * (yintercept - player->y));
            break;
        }
        xintercept += xstep;
        yintercept += ystep;
    }

    // Vertical intersections
    float vert_x, vert_y, vert_dx, vert_dy;
    vert_x = floor(player->x / TILE_SIZE) * TILE_SIZE;
    vert_x += (ray_dx > 0) ? TILE_SIZE : 0;
    vert_y = player->y + (vert_x - player->x) / ray_dx * ray_dy;

    vert_dx = TILE_SIZE * ((ray_dx > 0) ? 1 : -1);
    vert_dy = vert_dx * tan(ray->angle);

    while (vert_x >= 0 && vert_x < SW && vert_y >= 0 && vert_y < SH)
    {
        if (is_wall(vert_x - (ray_dx > 0 ? 0 : 1), vert_y, player))
        {
            ray->vertical_distance = sqrt((vert_x - player->x) * (vert_x - player->x) + (vert_y - player->y) * (vert_y - player->y));
            break;
        }
        vert_x += vert_dx;
        vert_y += vert_dy;
    }

    // Determine the shortest distance
    ray->distance = fmin(ray->horizontal_distance, ray->vertical_distance);
}

void clear_screen(t_player *player)
{
    // Fill the image data with a solid color (e.g., black)
    int color = 0x000000; // Background color (black)
    for (int y = 0; y < SH; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            put_pixel(player, x, y, color); // Fill every pixel with the background color
        }
    }
}

void render_3d_wall_slice(t_player *player, int ray_id, float distance)
{
    float angle_diff = player->rays[ray_id].angle - player->rotationAngle;
    float corrected_distance = distance * cos(angle_diff);
    int wall_height = (TILE_SIZE * SH) / corrected_distance;
    int wall_top = (SH / 2) - (wall_height / 2);
    if (wall_top < 0) wall_top = 0;

    int wall_bottom = (SH / 2) + (wall_height / 2);
    if (wall_bottom >= SH) wall_bottom = SH - 1;
    int x_pos = (SW / NUM_RAYS) * ray_id;
    int color = 0xFF0000;
    for (int y = wall_top; y <= wall_bottom; y++)
    {
        put_pixel(player, x_pos, y, color);
    }
}

void render_player(t_player *player)
{
    int player_x = (int)(player->x);
    int player_y = (int)(player->y);
    int radius = player->radius;

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int px = player_x + x;
                int py = player_y + y;

                if (px >= 0 && px < SW && py >= 0 && py < SH)
                {
                    put_pixel(player, px, py, 0xFFFF00);
                }
            }
        }
    }
}

void cast_all_rays(t_player *player)
{
    clear_screen(player);
    draw_floor_and_ceiling(player);
    float ray_angle = player->rotationAngle - (FOV_ANGLE / 2);

    for (int i = 0; i < NUM_RAYS; i++)
    {
        player->rays[i].angle = ray_angle;
        cast_ray(player, &player->rays[i]);
        if (player->rays[i].distance > 0)
            render_3d_wall_slice(player, i, player->rays[i].distance);
        ray_angle += FOV_ANGLE / NUM_RAYS;
    }
}

int key_eshap(int keycode, t_player *player)
{
    float new_x = player->x;
    float new_y = player->y;

    if (keycode == 123)
        player->rotationAngle -= player->rotationSpeed;
    else if (keycode == 124)
        player->rotationAngle += player->rotationSpeed;
    else if (keycode == 126)
    {
        new_x += cos(player->rotationAngle) * player->moveSpeed;
        new_y += sin(player->rotationAngle) * player->moveSpeed;
    }
    else if (keycode == 125)
    {
        new_x -= cos(player->rotationAngle) * player->moveSpeed;
        new_y -= sin(player->rotationAngle) * player->moveSpeed;
    }
    if (!is_wall(new_x, new_y,player))
    {
        player->x = new_x;
        player->y = new_y;
    }
    clear_image(player);
    draw_map(player); // Redraw the map onto the image
    draw_player(player); // Draw the player onto the image
    cast_all_rays(player);
    mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0); // Display the image
    return (0);
}

int close_window(t_player *player)
{
    if (player->map)
    {
        for (int i = 0; player->map[i]; i++)
        {
            free(player->map[i]);
        }
        free(player->map);
    }
    mlx_destroy_window(player->mlx, player->window);
    exit(0);
    return 0;
}

void draw_floor_and_ceiling(t_player *player)
{
    int y;
    for (y = 0; y < SH / 2; y++) // From top to middle
    {
        for (int x = 0; x < SW; x++)
        {
            //hena diri player->ciel_color
            put_pixel(player, x, y, CEILING_COLOR); // Fill the ceiling
        }
    }
    for (y = SH / 2; y < SH; y++) // From middle to bottom
    {
        for (int x = 0; x < SW; x++)
        {
            //hena diri floor_color
            put_pixel(player, x, y, FLOOR_COLOR); // Fill the floor
        }
    }
}

int main(int ac , char **av)
{
    t_player p;

    if (ac != 2)
        return (ft_putstr_fd("USGAE .cub3D <name_map.cub>", 2), 1);
    if (checkfilename(av[1]) == -1)
		return (ft_putstr_fd("Invalid extension file name\n", 2), 1);
    init_data(&p);
    if (ft_read_map(av[1], &p) == -1)
        return (ft_putstr_fd("Error reading map\n", 2), 1);
    if (!valid_map(&p))
        return (write(2, "Invalid map\n", 12), 1);
    p.mlx = mlx_init();
    if (!(p.mlx))
        return (1);
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!(p.window))
        return (1);
    p.img = mlx_new_image(p.mlx, SW, SH);
    if (!(p.img))
        return (1);
    p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
    if (!(p.img_data))
        return (1);
    clear_image(&p);
    // draw_map(&p);
    // draw_player(&p);
    cast_all_rays(&p);
    // printf("color=%d\n",p.floor_color);
    // printf("texture=%s\n", p.no);
    mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
    // mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
    // mlx_hook(p.window, 17, 0, close_window, &p);
    mlx_loop(p.mlx);
    return (0);
}
