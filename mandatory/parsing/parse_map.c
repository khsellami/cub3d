/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:02:49 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/06 18:00:41 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	stocke_map_line(char *line, int size, t_player *p, int j)
{
	char	*map_content;
	int		i;

	map_content = malloc(size + 1);
	if (!map_content)
		return ;
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
		ft_strcpy(p->map[j], map_content);
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

int	count_map_lines(int fd, int *longest_line)
{
	char	*line;
	int		map_size;
	char	*trimmed;

	*longest_line = 0;
	map_size = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (ft_strncmp(trimmed, "F ", 2) && ft_strncmp(trimmed, "C ", 2) \
		&& ft_strncmp(trimmed, "NO ", 3) && ft_strncmp(trimmed, "SO ", 3) \
		&& ft_strncmp(trimmed, "EA ", 3) && ft_strncmp(trimmed, "WE ", 3))
		{
			map_size++;
			if (ft_strlen(line) > *longest_line)
				*longest_line = ft_strlen(line);
		}
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	return (map_size);
}

void	read_map_lines(int fd, int longest_line, t_player *p)
{
	char	*line;
	int		j;
	char	*trimmed;

	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n");
		if (trimmed && trimmed[0] != 'F' && trimmed[0] != 'C' \
		&& ft_strncmp(trimmed, "NO ", 3) != 0 \
		&& ft_strncmp(trimmed, "SO ", 3) != 0 \
		&& ft_strncmp(trimmed, "EA ", 3) != 0 \
		&& ft_strncmp(trimmed, "WE ", 3) != 0 \
		&& !just_spaces(trimmed))
		{
			stocke_map_line(line, longest_line, p, j);
			j++;
		}
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	p->map[j] = NULL;
}

int	ft_read_map(char **av, t_player *p)
{
	int		fd;
	int		map_size;
	int		longest_line;
	int		j;

	j = 0;
	p->map = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	map_size = count_map_lines(fd, &longest_line);
	close(fd);
	p->map = malloc(sizeof(char *) * (map_size + 1));
	if (!p->map)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (free(p->map), -1);
	read_map_lines(fd, longest_line, p);
	close(fd);
	return (0);
}
