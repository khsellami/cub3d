/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:46:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:39:30 by ksellami         ###   ########.fr       */
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
// int is_map_line(char *line)
// {
//     int i = 0;

//     // A map line must contain at least one '1', '0', 'N', 'S', 'E', or 'W'.
//     // Iterate through each character of the line.
//     while (line[i])
//     {
//         // Check if the character is valid for a map (spaces are allowed inside the map).
//         if (line[i] != ' ' && line[i] != '1' && line[i] != '0' &&
//             line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
//             return (0); // If a character is invalid, return false.
//         i++;
//     }

//     // If we reach this point, all characters in the line are valid map elements.
//     // Make sure the line isn't empty.
//     return (i > 0);
// }

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
        game->floor_color = (r << 16) | (g << 8) | b; // Combine RGB values into a single integer
    else if (ft_strncmp(line - 2, "C ", 2) == 0)
        game->ceiling_color = (r << 16) | (g << 8) | b;

    // Free memory used for the color components
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


int parse_map(t_game *game, char *map_file)
{
    (void)game;
    int fd;
    char *line;
    int map_start = 0;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Error opening file\n", 2), 0);

    // Read the file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        // printf("Processing line: [%s]\n", line); // Debug: print each line as it's processed

        // Skip empty lines or lines that contain only spaces
        if (line[0] == '\0' || ft_str_only_contains_spaces(line))
        {
            // printf("Skipping empty line or line with only spaces.\n");
            free(line);
            continue;
        }

        // Check if the line is a texture definition
        if (is_texture_line(line))
        {
            // printf("***Texture detected*** [%s]\n", line);
            parse_texture(game, line);
        }
        // Check if the line is a color definition (floor or ceiling)
        else if (is_color_line(line))
        {
            // printf("***Color detected*** [%s]\n", line);
            parse_color(game, line);
        }
        // Check if the line is part of the map
        else if (is_map_line(line))
        {
            // printf("***Map line detected*** [%s]\n", line);
            add_line_to_map(game, line, map_start++);
        }
        else
        {
            printf("***Invalid line detected*** [%s]\n", line);
            free(line);
            return (ft_putstr_fd("Invalid map format\n", 2), 0);
        }

        free(line);
    }
    close(fd);
    return (1);
}

