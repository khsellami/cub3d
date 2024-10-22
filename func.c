/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:25 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/22 17:38:11 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int check_double_texture(char **map)
{
    int found[4] = {0, 0, 0, 0};  // Track if NO, SO, WE, EA are found

    if (!map)
        return (0);

    for (int i = 0; map[i]; i++)
    {
        if (ft_strncmp(map[i], "NO", 2) == 0)
            found[0]++;
        else if (ft_strncmp(map[i], "SO", 2) == 0)
            found[1]++;
        else if (ft_strncmp(map[i], "WE", 2) == 0)
            found[2]++;
        else if (ft_strncmp(map[i], "EA", 2) == 0)
            found[3]++;
    }

    // Check if all textures are present exactly once
    for (int j = 0; j < 4; j++)
    {
        if (found[j] != 1)
        {
            printf("Error: Missing or duplicate texture identifier\n");
            return (0);
        }
    }

    return (1);
}

int check_colors(char **split, Player *player)
{
    if (!split || !player)
        return (0);

    if (ft_strcmp(split[0], "F") == 0)  // Floor color
    {
        if (!parse_color(split[1], &player->floor))
            return (0);
    }
    else if (ft_strcmp(split[0], "C") == 0)  // Ceiling color
    {
        if (!parse_color(split[1], &player->ceiling))
            return (0);
    }
    else
    {
        printf("Invalid color identifier: %s\n", split[0]);
        return (0);
    }
    return (1);
}


void free_texture(char **split)
{
    int i = 0;

    if (!split)
        return;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void add_texture(Player *player, char *path, char *key)
{
    if (!path || !key)
        return;

    if (ft_strcmp(key, "NO") == 0)
        player->textures.north = ft_strdup(path);
    else if (ft_strcmp(key, "SO") == 0)
        player->textures.south = ft_strdup(path);
    else if (ft_strcmp(key, "WE") == 0)
        player->textures.west = ft_strdup(path);
    else if (ft_strcmp(key, "EA") == 0)
        player->textures.east = ft_strdup(path);
    else
        printf("Invalid texture key: %s\n", key);
}

int parse_color(char *color_str, int *color)
{
    char **rgb = ft_split(color_str, ',');
    int r, g, b;

    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        return (free_texture(rgb), 0);

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_texture(rgb);
        printf("Invalid RGB values: %d, %d, %d\n", r, g, b);
        return (0);
    }

    *color = (r << 16) | (g << 8) | b;  // Pack RGB into a single int
    free_texture(rgb);
    return (1);
}
int ft_make_texture(Player *player, int j)
{
    char **split;
    char *trimmed;

    while (player->map[j])
    {
        split = ft_split(player->map[j], ' ');  // Split line by spaces
        if (split[1])
        {
            trimmed = ft_strtrim(split[1], " \t\n");
            free(split[1]);
            split[1] = trimmed;
        }
        else
        {
            free_texture(split);
            break;
        }

        add_texture(player, split[1], split[0]);  // Add texture

        if (!check_colors(split, player))  // Validate colors
        {
            free_texture(split);
            return (0);
        }

        free_texture(split);
        j++;
    }
    return (check_double_texture(player->map));  // Ensure textures are valid
}

