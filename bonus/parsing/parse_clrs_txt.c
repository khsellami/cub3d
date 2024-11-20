/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs_txt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:45:36 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/20 17:32:53 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	parse_texture_line(char *trimmed, t_player *p)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		if (p->no != NULL)
			return (-1);
		p->no = parse_texture(trimmed + 3);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		if (p->so != NULL)
			return (-1);
		p->so = parse_texture(trimmed + 3);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		if (p->ea != NULL)
			return (-1);
		p->ea = parse_texture(trimmed + 3);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		if (p->we != NULL)
			return (-1);
		p->we = parse_texture(trimmed + 3);
	}
	return (0);
}

int	parse_color_line(char *trimmed, t_player *p)
{
	if (trimmed[0] == 'F' && trimmed[1] == ' ')
	{
		if (p->floor_color != -1)
			return (-1);
		return (parse_color(trimmed + 2, &p->floor_color));
	}
	else if (trimmed[0] == 'C' && trimmed[1] == ' ')
	{
		if (p->ciel_color != -1)
			return (-1);
		return (parse_color(trimmed + 2, &p->ciel_color));
	}
	return (0);
}

int	is_map_line(char *line)
{
	return ((ft_strchr(line, '0') || \
	ft_strchr(line, '1')) && !ft_strchr(line, ','));
}

int	process_trimmed_line(char *trimmed, t_player *p, int fd)
{
	if (trimmed && trimmed[0] && is_texture_line(trimmed))
	{
		if (parse_texture_line(trimmed, p) == -1)
			return (free(trimmed), close(fd), -1);
	}
	if (trimmed && trimmed[0] && trimmed[1] \
	&& (trimmed[0] == 'C' || trimmed[0] == 'F'))
	{
		if (parse_color_line(trimmed, p) == -1)
			return (free(trimmed), close(fd), -1);
	}
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
		if (is_map_line(line))
		{
			free(line);
			break ;
		}
		if (space_line(line))
			return (-1);
		trimmed = ft_strtrim(line, " ");
		free(line);
		if (process_trimmed_line(trimmed, p, fd) == -1)
			return (-1);
		free(trimmed);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
