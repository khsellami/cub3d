/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clr_txt_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:58:54 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 21:34:14 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*parse_texture(char *line)
{
	return (ft_strtrim(line, " \t\n"));
}

int	is_valid_color(int color)
{
	return (color >= 0 && color <= 255);
}

int	parse_color(char *line, int *color)
{
	char 	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (!components || array_len(components) != 3)
		return (ft_putstr_fd("Invalid color format\n", 2), -1);
	r = atoi(components[0]);
	g = atoi(components[1]);
	b = atoi(components[2]);
	if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
		return (ft_putstr_fd("Color values must be between 0 and 255\n", 2), -1);
	*color = (r << 16) | (g << 8) | b;
	free_array(components);
	return (1);
}

int check_clr_txt(t_player *p)
{
	if (p->no== NULL || p->so == NULL || p->ea == NULL \
	|| p->we == NULL)
		return (1);
	return (0);
}
