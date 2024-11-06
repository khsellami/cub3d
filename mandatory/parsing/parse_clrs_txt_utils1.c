/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs_txt_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:47:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/06 17:09:35 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	char	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (!components || array_len(components) != 3)
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
