/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:22:30 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 11:24:42 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is_valid_color(int color)
{
    return (color >= 0 && color <= 255);
}

int parse_color(char *line, int *color)
{
    char **components = ft_split(line, ',');
    if (!components || array_len(components) != 3)
        return (ft_putstr_fd("Invalid color format\n", 2), -1);
    int r = atoi(components[0]);
    int g = atoi(components[1]);
    int b = atoi(components[2]);
    if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
        return (ft_putstr_fd("Color values must be between 0 and 255\n", 2), -1);
    *color = (r << 16) | (g << 8) | b;
    free_array(components);
    return (1);
}

void set_player_orientation(t_player *player, char orientation)
{
    if (orientation == 'N')
        player->angle = 90;
    else if (orientation == 'S')
        player->angle = 270;
    else if (orientation == 'E')
        player->angle = 0;
    else if (orientation == 'W')
        player->angle = 180;
}

int parse_textures(char *line, char **texture_path)
{
    char *path = ft_strtrim(line, " ");
    if (!path || !*path)
        return (ft_putstr_fd("Invalid texture path\n", 2), -1);
    *texture_path = path;
    return (1);
}

int parse_line(char *line, t_player *player)
{
    if (ft_strncmp(line, "C ", 2) == 0)
        return (parse_color(line + 2, &player->ciel_color));
    else if (ft_strncmp(line, "F ", 2) == 0)
        return (parse_color(line + 2, &player->floor_color));
    else if (ft_strncmp(line, "NO ", 3) == 0)
        return (parse_textures(line + 3, &player->no));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return (parse_textures(line + 3, &player->so));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return (parse_textures(line + 3, &player->ea));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return (parse_textures(line + 3, &player->we));
    return (0);
}
