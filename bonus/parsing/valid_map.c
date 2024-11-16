/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:26:24 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/16 16:13:34 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	in_map(char c)
{
	return (c == '0' || c == '1');
}

int	entoure_mur(t_player *p, int i, int j)
{
	if (p->map && (!p->map[i + 1] || !in_map(p->map[i + 1][j])))
		return (0);
	if (p->map && (i - 1 < 0 || !in_map(p->map[i - 1][j])))
		return (0);
	if (p->map && (!p->map[i][j + 1] || !in_map(p->map[i][j + 1])))
		return (0);
	if (p->map && (j - 1 < 0 || !in_map(p->map[i][j - 1])))
		return (0);
	return (1);
}

int	invalid_text(char *s)
{
	int	len;

	if (!s)
		return (1);
	len = ft_strlen(s);
	if (len < 4 || s[len - 1] != 'm' || s[len - 2] != 'p' \
	|| s[len - 3] != 'x' || s[len - 4] != '.')
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(1);
	}
	return (0);
}

int	invalid_extension_txt(t_player *p)
{
	if (invalid_text(p->no) || invalid_text(p->so) \
	|| invalid_text(p->ea) || invalid_text(p->we))
		return (1);
	return (0);
}

int	valid_map(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (!valid_char_map(p->map[i][j]))
				return (0);
			if (p->map[i][j] == ' ' && !valid_space(p, i, j))
				return (0);
			if (p->map[i][j] == '0' && !entoure_mur(p, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (invalid_extension_txt(p))
		return (ft_putstr_fd("ERROR\nInvalid textures extension\n", 2), 1);
	return (1);
}
