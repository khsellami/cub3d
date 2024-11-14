/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs_txt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:45:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/13 18:28:07 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	parse_texture_line(char *trimmed, t_player *p)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		p->no = parse_texture(trimmed + 3);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		p->so = parse_texture(trimmed + 3);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		p->ea = parse_texture(trimmed + 3);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		p->we = parse_texture(trimmed + 3);
}

int	parse_color_line(char *trimmed, t_player *p)
{
	// printf("trimmed = [%s]\n", trimmed);
	if (trimmed[0] == 'F' && trimmed[1] == ' ' && p->floor_color == -1)
		return (parse_color(trimmed + 2, &p->floor_color));
	else if (trimmed[0] == 'C' && trimmed[1] == ' ' && p->ciel_color == -1) 
		return (parse_color(trimmed + 2, &p->ciel_color));
	return (0);
}

int	parse_colors_textures(char **av, t_player *p)
{
	int		fd;
	char	*line;
	char	*trimmed;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		free(line);
		if (parse_color_line(trimmed, p) == -1)
			return (free(trimmed), close(fd), -1);
		parse_texture_line(trimmed, p);
		free(trimmed);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
