/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/24 19:45:53 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_player(t_player *p)
{
    p->x = SW / 2;
    p->y = SH / 2;
    p->radius = 3;
    p->rotationAngle = M_PI / 2;
    p->moveSpeed = 2.0;
    p->rotationSpeed = 2 * (M_PI / 180);
}

void clear_image(t_player *player)
{
    int img_size = SW * SH * 4; // 4 bytes per pixel for RGBA
    memset(player->img_data, 0, img_size); // Set all pixels to 0 (black)
}

void put_pixel(t_player *player, int x, int y, int color)
{
    if (x >= 0 && x < SW && y >= 0 && y < SH)  // Ensure coordinates are within the screen bounds
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

void draw_map(t_player *player)
{
    int i = 0, j, color;
    while (player->map[i])
    {
        j = 0;
        while (player->map[i][j])
        {
            color = (player->map[i][j] == '1') ? 0xFFFFFF : 0x000000; // RED for '1', BLACK for '0'
            for (int y = i * TILE_SIZE; y < (i + 1) * TILE_SIZE; y++)
            {
                for (int x = j * TILE_SIZE; x < (j + 1) * TILE_SIZE; x++)
                {
                    put_pixel(player, x, y, color);
                }
            }
            j++;
        }
        i++;
    }
}

int is_wall(float x, float y, t_player *p)
{
    int mapX = (int)(x / TILE_SIZE);
    int mapY = (int)(y / TILE_SIZE);

    if (mapX < 0 || mapY < 0 || mapX >= MAP_NUM_COLS || mapY >= MAP_NUM_ROWS)
        return 1;
    return (p->map[mapY][mapX] == '1');
}

void cast_ray(t_player *player, t_ray *ray)
{
    float ray_x = player->x;
    float ray_y = player->y;
    float ray_dx = cos(ray->angle);
    float ray_dy = sin(ray->angle);

    while (ray_x >= 0 && ray_x < SW && ray_y >= 0 && ray_y < SH)
    {
        if (is_wall(ray_x, ray_y,player))
        {
            ray->distance = sqrt((ray_x - player->x) * (ray_x - player->x) + (ray_y - player->y) * (ray_y - player->y));
            return;
        }
        ray_x += ray_dx;
        ray_y += ray_dy;
    }
    ray->distance = -1;
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
    // Correct the fish-eye distortion
    float angle_diff = player->rays[ray_id].angle - player->rotationAngle;
    float corrected_distance = distance * cos(angle_diff);

    // Calculate the wall height based on the corrected distance
    int wall_height = (TILE_SIZE * SH) / corrected_distance;

    // Calculate the starting and ending Y positions for the wall slice
    int wall_top = (SH / 2) - (wall_height / 2);
    if (wall_top < 0) wall_top = 0;

    int wall_bottom = (SH / 2) + (wall_height / 2);
    if (wall_bottom >= SH) wall_bottom = SH - 1;

    // Calculate the x position based on ray_id
    int x_pos = (SW / NUM_RAYS) * ray_id; // Position for the current slice

    // Fill the wall slice with a solid color (you can vary this based on distance)
    int color = 0xFF0000; // Example: Red for walls (you can change this based on distance)
    for (int y = wall_top; y <= wall_bottom; y++)
    {
        put_pixel(player, x_pos, y, color); // Draw each pixel in the slice
    }
}




void cast_all_rays(t_player *player)
{
    clear_screen(player); // Clear the screen before drawing

    float ray_angle = player->rotationAngle - (FOV_ANGLE / 2); // Start from the leftmost ray

    for (int i = 0; i < NUM_RAYS; i++)
    {
        player->rays[i].angle = ray_angle; // Store the angle of the current ray
        cast_ray(player, &player->rays[i]); // Perform raycasting to find wall hit

        // Render the corresponding 3D wall slice for this ray
        if (player->rays[i].distance > 0)
        {
            render_3d_wall_slice(player, i, player->rays[i].distance);
        }

        ray_angle += FOV_ANGLE / NUM_RAYS; // Increment angle based on the total number of rays
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

int ft_read_map(char *file, t_player *player)
{
    int fd;
    char *line;
    int i = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return -1;
    }
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '1' || line[0] == ' ')
            i++;
        free(line);
        line = get_next_line(fd);
    }
    // Allocate memory for the map
    player->map = malloc(sizeof(char *) * (i + 1));
    if (!player->map)
    {
        close(fd);
        printf("Error allocating memory for map\n");
        return -1;
    }
    // Reset file pointer
    lseek(fd, 0, SEEK_SET);
    int j = 0;
    line = get_next_line(fd);
    while (line && j < i) {
        if (line[0] == '1' || line[0] == ' ')
        {
            player->map[j] = malloc(strlen(line) + 1);
            if (!player->map[j])
            {
                for (int k = 0; k < j; k++)
                    free(player->map[k]);
                free(player->map);
                close(fd);
                printf("Error allocating memory for map line\n");
                return -1;
            }
            strcpy(player->map[j], line);

            // Check for 'N' in the current line
            char *n_pos = strchr(player->map[j], 'N');
            if (n_pos) {
                // Calculate player position in pixels based on 'N' location
                int x_pos = n_pos - player->map[j]; // Column index of 'N'
                int y_pos = j; // Row index of 'N'

                // Set the player's position in the map
                player->x = (x_pos * TILE_SIZE) + (TILE_SIZE / 2);
                player->y = (y_pos * TILE_SIZE) + (TILE_SIZE / 2);

                // Replace 'N' with '0' so it's treated as an empty space
                *n_pos = '0';
            }

            j++;
        }
        free(line);
        line = get_next_line(fd);
    }

    // Null terminate the map
    player->map[j] = NULL;

    close(fd);
    return 0;
}

int main(int ac , char **av)
{
    (void)ac;
    t_player p;
    
    init_player(&p);
    if (ft_read_map(av[1], &p) == -1)
    {
        printf("Error reading map\n");
        return EXIT_FAILURE;
    }
    p.mlx = mlx_init();
    if (!(p.mlx))
        return (0);
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!(p.window))
        return (0);
    
    p.img = mlx_new_image(p.mlx, SW, SH);
    p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
    clear_image(&p);
    draw_map(&p);
    draw_player(&p);
    cast_all_rays(&p);
    mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
    mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
    mlx_hook(p.window, 17, 0, close_window, &p);
    mlx_loop(p.mlx);
    return (0);
}

