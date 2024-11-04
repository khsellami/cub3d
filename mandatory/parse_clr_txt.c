/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clr_txt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:56:04 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 22:14:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_colors_textures(int ac, char **av, t_player *p)
{
	int		fd;
	char	*line;
	char	*trimmed;

	if (ac != 2)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (trimmed[0] == 'F')
		{
			if (parse_color(trimmed + 2, &p->floor_color) == -1)
			{
				free(trimmed);
				free(line);
				close(fd);
				return (-1);
			}
		}
		else if (trimmed[0] == 'C')
		{
			if (parse_color(trimmed + 2, &p->ciel_color) == -1)
			{
				free(trimmed);
				free(line);
				close(fd);
				return (-1);
			}
		}
		else if (ft_strncmp(trimmed, "NO ", 3) == 0)
			p->no = parse_texture(trimmed + 3);
		else if (ft_strncmp(trimmed, "SO ", 3) == 0)
			p->so = parse_texture(trimmed + 3);
		else if (ft_strncmp(trimmed, "EA ", 3) == 0)
			p->ea = parse_texture(trimmed + 3);
		else if (ft_strncmp(trimmed, "WE ", 3) == 0)
			p->we = parse_texture(trimmed + 3);
		free(trimmed);
		free(line);
	}
	close(fd);
	return (0);
}
