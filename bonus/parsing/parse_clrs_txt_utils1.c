/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs_txt_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:47:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/20 13:17:04 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	check_comp(char **components)
{
	int		i;
	char	*trimmed;

	trimmed = NULL;
	i = 0;
	while (components[i])
	{
		trimmed = ft_strtrim(components[i], " \n");
		if (!only_digits(trimmed))
			return (free(trimmed), -1);
		free(trimmed);
		i++;
	}
	return (0);
}

int	nbr_virgules(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	parse_color(char *line, int *color)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	if (nbr_virgules(line) != 2)
		return (-1);
	components = ft_split(line, ',');
	if (!components || array_len(components) != 3)
		return (-1);
	if (check_comp(components) == -1)
		return (-1);
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
		return (-1);
	*color = (r << 16) | (g << 8) | b;
	free_array(components);
	return (1);
}

int	check_clr_txt(t_player *p)
{
	if (p->no == NULL || p->so == NULL || p->ea == NULL \
	|| p->we == NULL || p->floor_color == -1 \
	|| p->ciel_color == -1)
		return (1);
	return (0);
}

int	is_texture_line(char *trimmed)
{
	return (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3) \
	|| !ft_strncmp(trimmed, "EA ", 3) || !ft_strncmp(trimmed, "WE ", 3));
}
