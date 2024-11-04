/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:02:49 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 19:31:20 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	stocke_map_line(char *line, int size, t_player *p, int j)
{
	char	*map_content;
	int		i;

	map_content = malloc(size + 1);
	if (!map_content)
		return;
	i = 0;
	while (i < size && line[i])
	{
		map_content[i] = line[i];
		i++;
	}
	while (i < size)
		map_content[i++] = ' ';
	map_content[i] = '\0';
	p->map[j] = malloc(size + 1);
	if (p->map[j])
		strcpy(p->map[j], map_content);
	free(map_content);
}

int	just_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n'))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int ft_parsing(int ac , char **av , t_player *p)
{
	int		fd;
	char	*line;
	int		map_size;
	int		longest_line;
	int		j;
	char	*trimmed;

	(void)ac;
	j = 0;
	p->map = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	map_size = 0;
	longest_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (strncmp(trimmed, "F ", 2) && strncmp(trimmed, "C ", 2) &&
			strncmp(trimmed, "NO ", 3) && strncmp(trimmed, "SO ", 3) &&
			strncmp(trimmed, "EA ", 3) && strncmp(trimmed, "WE ", 3))
			{
			map_size++;
			if ((int)ft_strlen(line) > longest_line)
				longest_line = (int)strlen(line);
		}
		free(trimmed);
		free(line);
	}
	close(fd);
	p->map = malloc(sizeof(char *) * (map_size + 1));
	if (!p->map)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (trimmed[0] != 'F' && trimmed[0] != 'C' &&
			strncmp(trimmed, "NO ", 3) != 0 && strncmp(trimmed, "SO ", 3) != 0 &&
			strncmp(trimmed, "EA ", 3) != 0 && strncmp(trimmed, "WE ", 3) != 0 &&
			!just_spaces(trimmed))
		{
			stocke_map_line(line, longest_line, p, j);
			j++;
		}
		free(trimmed);
		free(line);
	}
	p->map[j] = NULL;
	close(fd);
	return (0);
}
