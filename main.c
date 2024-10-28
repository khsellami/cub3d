/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 22:41:56 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void init_data(t_player *p)
{
    int i;

    i = 0;
    p->x = SW / 2;
    p->y = SH / 2;
    p->angle = 0;
    p->radius = 3;
    p->rotationAngle = M_PI / 2;
    p->moveSpeed = 2.0;
    p->rotationSpeed = 2 * (M_PI / 180);
    p->mlx = NULL;
    p->window = NULL;
    p->img = NULL;
    p->img_data = NULL;
    p->bpp = 0;
    p->line_length = 0;
    p->endian = 0;
    p->no = NULL;
    p->so = NULL;
    p->ea = NULL;
    p->we = NULL;
    p->floor_color = 0x000000;
    p->ciel_color = 0xFFFFFF;
    p->map = NULL;
    while (i < NUM_RAYS)
    {
        p->rays[i].horizontal_distance = 0;
        p->rays[i].vertical_distance = 0;
        p->rays[i].distance = 0.0;
        p->rays[i].angle = 0.0;
        i++;
    }
}

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

void horizontal_ray_intersection(t_player *player, t_ray *ray) {
    float xintercept, yintercept, xstep, ystep;

    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += (sin(ray->angle) > 0) ? TILE_SIZE : 0;
    xintercept = player->x + (yintercept - player->y) / tan(ray->angle);
    
    ystep = TILE_SIZE * ((sin(ray->angle) > 0) ? 1 : -1);
    xstep = ystep / tan(ray->angle);
    
    while (xintercept >= 0 && xintercept < SW && yintercept >= 0 && yintercept < SH) {
        if (is_wall(xintercept, yintercept - (sin(ray->angle) > 0 ? 0 : 1), player)) {
            ray->horizontal_distance = sqrt((xintercept - player->x) * (xintercept - player->x) +
                                             (yintercept - player->y) * (yintercept - player->y));
            break;
        }
        xintercept += xstep;
        yintercept += ystep;
    }
}

void vertical_ray_intersection(t_player *player, t_ray *ray) {
    float vert_x, vert_y, vert_dx, vert_dy;

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

void cast_ray(t_player *player, t_ray *ray) {
    ray->horizontal_distance = INT_MAX;
    ray->vertical_distance = INT_MAX;

    horizontal_ray_intersection(player, ray);
    vertical_ray_intersection(player, ray);

    ray->distance = fmin(ray->horizontal_distance, ray->vertical_distance);
}


void clear_screen(t_player *player)
{
    int color = 0x000000;
    for (int y = 0; y < SH; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            put_pixel(player, x, y, color);
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
    
    int x_pos = (ray_id * SW) / NUM_RAYS;
    int texture_index = (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance) ?
                        (cos(player->rays[ray_id].angle) > 0 ? 2 : 3) :
                        (sin(player->rays[ray_id].angle) > 0 ? 0 : 1);
    t_img *texture = NULL;
    if (texture_index == 0)
        texture = &player->no_img;
    else if (texture_index == 1)
        texture = &player->so_img;
    else if (texture_index == 2)
        texture = &player->ea_img;
    else if (texture_index == 3)
        texture = &player->we_img;
    if (!texture || !texture->img) {
        printf("Erreur: La texture %d n'est pas chargée correctement\n", texture_index);
        return;
    }
    int texture_x = (int)(fmod(player->rays[ray_id].distance, TILE_SIZE) * texture->width / TILE_SIZE);
    if (texture_x < 0 || texture_x >= texture->width) {
        printf("Erreur: texture_x %d est hors limites\n", texture_x);
        return;
    }
    for (int y = wall_top; y <= wall_bottom; y++)
    {
        int d = (y - wall_top) * texture->height / wall_height;
        int texture_y = d % texture->height;
        if (texture_y < 0 || texture_y >= texture->height) {
            printf("Erreur: texture_y %d est hors limites\n", texture_y);
            return;
        }
        int color = *(int *)(texture->data + (texture_y * texture->line_length + texture_x * (texture->bpp / 8)));
        if (color == 0)
            color = 0x00FF00;
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
        else
            printf("Ray %d has no valid distance.\n", i);
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
    draw_map(player); 
    draw_player(player);
    cast_all_rays(player);
    mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
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
    for (y = 0; y < SH / 2; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            put_pixel(player, x, y, player->ciel_color);
        }
    }
    for (y = SH / 2; y < SH; y++)
    {
        for (int x = 0; x < SW; x++)
        {
            put_pixel(player, x, y, player->floor_color);
        }
    }
}

int get_pixel_color(void *img, int x, int y, t_player *p) 
{
    char *data = mlx_get_data_addr(img, &p->bpp, &p->line_length, &p->endian);
    return *(int*)(data + (y * p->line_length + x * (p->bpp / 8)));
}

void *get_texture_data(t_texture *texture)
{
    int bpp;
    int line_length;
    int endian;
    void *addr;

    addr = mlx_get_data_addr(texture, &bpp, &line_length, &endian);
    if (!addr)
    {
        write(2, "Error getting image data\n", 25);
        exit(1);
    }
    return addr;
}
void init_player(t_player *player)
{
    player->mlx = mlx_init();
    if (!player->mlx)
    {
        printf("Erreur: Échec de l'initialisation de MiniLibX\n");
        exit(EXIT_FAILURE);
    }
}

int load_texture(t_player *player, char *path, t_img *texture)
{
    if (!player || !player->mlx || !texture || !path)
    {
        printf("Erreur: Paramètre(s) NULL détecté(s)\n");
        return 1;
    }
    if (access(path, F_OK) == -1)
    {
        printf("Erreur: Le fichier %s n'existe pas.\n", path);
        return 1;
    }
    printf("Chargement de l'image depuis: %s\n", path);
    texture->img = mlx_xpm_file_to_image(player->mlx, path, &texture->width, &texture->height);
    if (!texture->img) {
        printf("Erreur: Impossible de charger l'image %s\n", path);
        return 1;
    }
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
    if (!texture->data)
    {
        printf("Erreur: Impossible de récupérer les données de l'image\n");
        return 1;
    }
    printf("Image chargée avec succès: %s\n", path);
    return 0;
}

void init_textures(t_player *player)
{
    if (load_texture(player, "./wall_north.xpm", &player->no_img) ||
        load_texture(player, "./wall_south.xpm", &player->so_img) ||
        load_texture(player, "./wall_east.xpm", &player->ea_img) ||
        load_texture(player, "./wall_west.xpm", &player->we_img)) {
        printf("Erreur: Échec du chargement des textures\n");
        exit(EXIT_FAILURE);
    }
}
void draw_wall(t_player *p, int x, int wall_height, int texture_index)
{
    int y;
    float wall_top = (SH / 2) - (wall_height / 2);
    float wall_bottom = (SH / 2) + (wall_height / 2);

    t_img *current_texture = NULL;

    if (texture_index == 0)
        current_texture = &p->no_img;
    else if (texture_index == 1)
        current_texture = &p->so_img;
    else if (texture_index == 2)
        current_texture = &p->ea_img;
    else if (texture_index == 3)
        current_texture = &p->we_img;

    if (!current_texture || !current_texture->img)
    {
        printf("Erreur: Texture non chargée\n");
        return;
    }
    for (y = wall_top; y < wall_bottom; y++)
    {
        if (y < 0 || y >= SH) continue;
        int tex_y = (y - wall_top) * current_texture->height / wall_height;
        int tex_x = x % current_texture->width;
        int color = *(int *)(current_texture->data + 
                             (tex_y * current_texture->line_length + tex_x * (current_texture->bpp / 8)));
        put_pixel(p, x, y, color);
    }
}


int main(int ac, char **av)
{
    t_player p;

    if (ac != 2)
        return (ft_putstr_fd("USAGE: .cub3D <name_map.cub>\n", 2), 1);
    if (checkfilename(av[1]) == -1)
        return (ft_putstr_fd("Invalid extension file name\n", 2), 1);
    init_data(&p);
    if (ft_read_map(av[1], &p) == -1)
        return (ft_putstr_fd("Error reading map\n", 2), 1);
    if (!valid_map(&p))
        return (write(2, "Invalid map\n", 12), 1);
    printf("[%s]\n", p.no);
    printf("[%s]\n", p.so);
    printf("[%s]\n", p.ea);
    printf("[%s]\n", p.we);
    p.mlx = mlx_init(); // Initialize mlx
    if (!p.mlx) {
        printf("Erreur: Échec de l'initialisation de MiniLibX\n");
        return 1;
    }
    init_textures(&p);
    p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
    if (!p.window)
        return (1);
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
