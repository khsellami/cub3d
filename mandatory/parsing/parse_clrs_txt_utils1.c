/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clrs_txt_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:47:26 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/13 18:33:43 by kahmada          ###   ########.fr       */
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

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int check_comp(char **components)
{
	int	i;
	int	j;

	i = 0;

	while (components[i])
	{
		components[i] = ft_strtrim(components[i], " \t"); // Apply strtrim to each component
		j = 0;
		while (components[i][j])
		{
			if (!ft_isdigit(components[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
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
	//pur chaque compenent trim it then check every number 0 ==>> 9
	if (check_comp(components) == -1)
		return (-1);
	// printf("components[0] = [%s]\n", components[0]);
	// exit(0);
	r = ft_atoi(components[0]);
	// printf("r = [%d]\n", r);
	g = ft_atoi(components[1]);
	// printf("g = [%d]\n", g);
	b = ft_atoi(components[2]);
	// printf("b = [%d]\n", b);
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
