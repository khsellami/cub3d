/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:53:47 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/20 13:16:33 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	checkfilename(char *filename)
{
	int	len;
	int	fd;

	if (!filename)
		return (-1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub"))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}

int	valid_char_map(char c)
{
	if (c != ' ' && c != '0' && c != '1' && \
	c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '\n')
		return (0);
	return (1);
}

int	not_mur_or_space(char c)
{
	if (c != ' ' && c != '1' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

int	valid_space(t_player *p, int i, int j)
{
	if (p->map && p->map[i + 1] && not_mur_or_space(p->map[i + 1][j]))
		return (0);
	if (p->map && i - 1 >= 0 && not_mur_or_space(p->map[i - 1][j]))
		return (0);
	if (p->map && p->map[i][j + 1] && not_mur_or_space(p->map[i][j + 1]))
		return (0);
	if (p->map && j - 1 >= 0 && not_mur_or_space(p->map[i][j -1]))
		return (0);
	return (1);
}

char	*parse_texture(char *line)
{
	return (ft_strtrim(line, " \n"));
}
