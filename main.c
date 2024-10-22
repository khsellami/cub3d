/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/22 20:16:04 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
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

int add_col_text(int fd, Player *player, int last_size, int first)
{
    char *line;
    int i = 0;
    while ((line = get_next_line(fd)) > 0)
    {
        if (line[0] == '1' || line[0] == ' ')
        {
            player->map[i] = ft_strdup(line);
            if (first == 0)
            {
                last_size = ft_strlen(line);
                first = 1;
            }
            i++;
        }
        free(line);
    }
    return (last_size);
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
    }
    return (map);
}
int ft_map(Player *player)
{
    int i = 0;
    int j = 0;
    while (player->map[i])
    {
        j = 0;
        while (player->map[i][j])
        {
            if (player->map[i][j] != '1' && player->map[i][j] != ' ')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}
void ft_add_map(Player *player, char *line, int j)
{
    if (ft_strlen(line) >= 1)
    {
        player->map[j] = ft_strtrim(line, "\n");
        if (!player->map[j])
        {
            printf("Memory allocation error\n");
            exit(1);
        }
    }
    else
    {
        j--; 
    }
}


int ft_check_map(Player *player, int fd, int i, int first)
{
    char *line;
    int j =0;
    player->map2 = ft_calloc(i + 2, sizeof(char *));
    while(j <i)
    {
        line = get_next_line(fd);
        if (!line || line[0] == '\n' || !first)
        {
            free(line);
            continue;
        }
        ft_add_map(player, line, j);
        free(line);
        j++;
    }
    close(fd);
    return (ft_map(player));
}

void ft_mapped(int i, int fd, Player *player)
{
    int last_size = 0;
    int first = 0;

    player->map = ft_calloc(i + 2, sizeof(char *));
    if (!player->map)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    last_size = add_col_text(fd, player, last_size, first);
    if(!ft_check_map(player, fd, i, first))
    {
        printf("Error\n");
        exit(1);
    }
    player->size_f = last_size;
    close(fd);
}

void ft_replace(char **map)
{
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ')
                map[i][j] = '0';
            j++;
        }
        i++;
    }
}

int ft_read_map(char *file, Player *player)
{
    int fd;
    char *line;
    int j = 0;
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
    ft_replace(player->map);
    close(fd);
    return (ft_make_texture(player, j));
}

int ft_flor_ceiling(int *color)
{
    int r;
    int g;
    int b;
    if (color[0] == -1 || color[1] == -1 || color[2] == -1)
        return (-1);
    r = color[0] * 65536;
    g = color[1] * 256;
    b = color[2];
    *color = r + g + b;
    return (0);
}

int valid_texture(Player player)
{
    if (!player.textures.north || !player.textures.south ||
        !player.textures.west || !player.textures.east)
    {
        printf("Missing one or more textures.\n");
        return 0;
    }
    return 1;
}
int valid_map(Player player)
{
    if (!player.map || !player.map[0])
    {
        printf("Map is empty or not loaded.\n");
        return 0;
    }

    int player_found = 0;
    for (int i = 0; player.map[i]; i++)
    {
        for (int j = 0; player.map[i][j]; j++)
        {
            if (player.map[i][j] == 'P')
            {
                player_found = 1;
                break;
            }
        }
        if (player_found)
            break;
    }

    if (!player_found)
    {
        printf("Player start position not found in the map.\n");
        return 0;
    }

    return 1;
}

int ft_size_map(char **map)
{
    int height = 0;
    if (!map)
        return -1;
    while (map[height] != NULL)
    {
        height++;
    }
    return height;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    Player player = {0}; // Initialize player structure
    player.mlx_conex = mlx_init();
    
    if (!player.mlx_conex)
    {   
        printf("Error initializing MLX\n");
        return (EXIT_FAILURE);
    }

    // if (parsing(ac, av) == -1)
    // {
    //     printf("Error parsing arguments\n");
    //     return (EXIT_FAILURE);
    // }

    // if (ft_read_map(av[1], &player) == -1)
    // {
    //     printf("Error reading map\n");
    //     return (EXIT_FAILURE);
    // }

    player.mlx_window = mlx_new_window(player.mlx_conex, player.size_f * 10, player.height * 10, "Cub3D");
    
    if (!player.mlx_window)
    {
        printf("Error creating window\n");
        return (EXIT_FAILURE);
    }
    mlx_loop(player.mlx_conex);
    // if (ft_flor_ceiling(&player.floor) == -1 || ft_flor_ceiling(&player.ceiling) == -1)
    // {
    //     printf("Error setting floor or ceiling color\n");
    //     return (EXIT_FAILURE);
    // }

    // if (!valid_texture(player) || !valid_map(player))
    // {
    //     printf("Invalid textures or map\n");
    //     return (EXIT_FAILURE);
    // }

    // Add your rendering logic here
    // mlx_loop(player.mlx_conex); // Start the MLX loop

    return (EXIT_SUCCESS);
}
