/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:46:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 19:41:55 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
//This function checks if a line contains a texture identifier

int is_texture_line(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 ||
            ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 ||
            ft_strncmp(line, "EA ", 3) == 0);
}

int is_color_line(char *line)
{
    return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int is_map_line(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0' &&
            line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

void parse_texture(t_game *game, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        game->texture_north = ft_strdup(line + 3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        game->texture_south = ft_strdup(line + 3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        game->texture_west = ft_strdup(line + 3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        game->texture_east = ft_strdup(line + 3);
}

void parse_color(t_game *game, char *line)
{
    char **colors;
    int r, g, b;

    // Skip the identifier ("F " or "C ")
    line += 2;
    colors = ft_split(line, ','); // Use a split function like `ft_split` to split the line by commas
    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);

    if (ft_strncmp(line - 2, "F ", 2) == 0)
        game->floor_color = (r << 16) | (g << 8) | b; 
    else if (ft_strncmp(line - 2, "C ", 2) == 0)
        game->ceiling_color = (r << 16) | (g << 8) | b;
    free(colors[0]);
    free(colors[1]);
    free(colors[2]);
    free(colors);
}

void add_line_to_map(t_game *game, char *line, int index)
{
    game->map[index] = ft_strdup(line);
}

int ft_str_only_contains_spaces(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}
static int count_map_lines(char *map_file)
{
    int fd;
    char *line;
    int count = 0;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (-1); // Error handling

    while ((line = get_next_line(fd)) != NULL)
    {
        // Count non-empty map lines
        if (!ft_str_only_contains_spaces(line) && is_map_line(line))
            count++;
        free(line);
    }

    close(fd);
    return (count);
}


int parse_map(t_game *game, char *map_file)
{
    int fd;
    char *line;
    int map_start = 0;

    // Count the number of map lines
    int map_lines = count_map_lines(map_file);
    if (map_lines < 0)
        return (ft_putstr_fd("Error opening file\n", 2), 0);

    // Allocate memory for the map
    game->map = malloc((map_lines + 1) * sizeof(char *));
    if (!game->map)
        return (ft_putstr_fd("Memory allocation error\n", 2), 0);

    // Open the file again to parse
    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Error opening file\n", 2), 0);

    // Read the file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\0' || ft_str_only_contains_spaces(line))
        {
            free(line);
            continue;
        }

        if (is_texture_line(line))
            parse_texture(game, line);
        else if (is_color_line(line))
            parse_color(game, line);
        else if (is_map_line(line))
            add_line_to_map(game, line, map_start++);
        else
        {
            free(line);
            return (ft_putstr_fd("Invalid map format\n", 2), 0);
        }

        free(line);
    }
    close(fd);
    game->map[map_start] = NULL; // Mark the end of the map array
    return (1);
}
