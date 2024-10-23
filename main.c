/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/23 18:24:40 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void put_pixel(t_img *img, int x, int y, int color)
{
    if (x < 0 || x >= 400 || y < 0 || y >= 400) // Ensure x/y are within bounds
        return;

    char *pixel;

    pixel = img->pixel_ptr + (y * img->pix_len + x * (img->bit_par_px / 8));
    
    *(unsigned int *)pixel = color; // Set the pixel to the given color
}
void render_map(Player *player, t_img *img) {
    int tile_size = 10;
    int x, y, i, j;

    if (!player || !player->map) {
        printf("Error: Player or map is NULL\n");
        return;
    }

    for (i = 0; player->map[i] != NULL; i++) {
        printf("Rendering row %d\n", i);

        for (j = 0; player->map[i][j] != '\0'; j++) {
            printf("Accessing map[%d][%d] = %c\n", i, j, player->map[i][j]);

            if (player->map[i][j] == '1') {
                for (y = i * tile_size; y < (i + 1) * tile_size; y++) {
                    for (x = j * tile_size; x < (j + 1) * tile_size; x++) {
                        put_pixel(img, x, y, 0xFFFFFF);  // White for '1'
                    }
                }
            } else {
                for (y = i * tile_size; y < (i + 1) * tile_size; y++) {
                    for (x = j * tile_size; x < (j + 1) * tile_size; x++) {
                        put_pixel(img, x, y, 0x000000);  // Black for others
                    }
                }
            }
        }
    }

    printf("---------------hi\n");
    exit(0);
}

void init_image(Player *player)
{
    player->img.img_ptr = mlx_new_image(player->mlx_conex, 400, 400);
    
    if (!player->img.img_ptr) {
        printf("Error creating image\n");
        exit(1); // Handle error appropriately
    }

    player->img.pixel_ptr = mlx_get_data_addr(player->img.img_ptr,
                                              &player->img.bit_par_px,
                                              &player->img.pix_len,
                                              &player->img.bit_order);
}
void display_image(Player *player)
{
    mlx_put_image_to_window(player->mlx_conex, player->mlx_window, player->img.img_ptr, 0, 0);
}

int valid_file_name(char *f)
{
    int fd;

    if (!f || ft_strlen(f) < 4 || ft_strcmp(&f[ft_strlen(f) - 4], ".cub") != 0)
        return (0);
    fd = open(f, O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return (1);
}

int parsing(int ac, char **av)
{
    if (ac != 2)
        return (-1);
    if (!valid_file_name(av[1]))
        return (-1);
    return (0);
}
char **ft_calloc(int size, int size2)
{
    char **map;
    int i;
    
    map = malloc(sizeof(char *) * size);
    if (!map) return NULL;
    
    for (i = 0; i < size; i++)
    {
        map[i] = malloc(sizeof(char) * size2);
        if (!map[i])
        {
            while (i-- > 0) free(map[i]);
            free(map);
            return NULL;
        }
        memset(map[i], 0, sizeof(char) * size2); // Initialize memory to zero
    }
    return (map);
}

#define MAX_LINE_LENGTH 256

char *ft_strcpy(char *dest, const char *src)
{
    if (!dest || !src)
        return NULL;

    int i = 0;
    while (src[i] && i < MAX_LINE_LENGTH - 1) // Ensure we don't overflow
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // Null terminate
    return dest;
}

void ft_mapped(int i, int fd, Player *player)
{
    (void)fd;

    player->map = ft_calloc(i + 2, sizeof(char *));
    if (!player->map)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    for (int j = 0; j < i + 2; j++)
    {
        player->map[j] = malloc(sizeof(char) * MAX_LINE_LENGTH);
        if (!player->map[j])
        {
            while (j-- > 0) free(player->map[j]);
            free(player->map);
            printf("Memory allocation error\n");
            exit(1);
        }
    }
}

int ft_read_map(char *file, Player *player)
{
    int fd;
    char *line;
    
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return -1;
    }
    int i = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '1' || line[0] == ' ')
            i++;
        
        free(line);
        line = get_next_line(fd);
    }
    ft_mapped(i, fd, player);
    lseek(fd, 0, SEEK_SET);
    int j = 0;
    line = get_next_line(fd);
    while (line && j < i)
    {
        if (line[0] == '1' || line[0] == ' ')
        {
            ft_strcpy(player->map[j], line);
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd); 
    return 0;
}

int main(int ac, char **av)
{
    Player player = {0};

    player.mlx_conex = mlx_init();
    
    if (!player.mlx_conex) {
        printf("Error initializing MLX\n");
        return EXIT_FAILURE;
    }

    if (parsing(ac, av) == -1) {
        printf("Error parsing arguments\n");
        return EXIT_FAILURE;
    }

    if (ft_read_map(av[1], &player) == -1) {
        printf("Error reading map\n");
        return EXIT_FAILURE;
    }

    player.mlx_window = mlx_new_window(player.mlx_conex, 400, 400, "Cub3D");
    
    if (!player.mlx_window) {
        printf("Error creating window\n");
        return EXIT_FAILURE;
    }

    init_image(&player);
    
    render_map(&player, &player.img);
    
    display_image(&player);

    mlx_loop(player.mlx_conex);

    return EXIT_SUCCESS; // Use EXIT_SUCCESS for successful completion
}

