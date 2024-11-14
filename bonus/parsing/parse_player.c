/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:01:31 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/13 18:22:34 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	update_player(t_player *p, char direction)
{
	if (direction == 'N')
		p->angle = M_PI / 2;
	else if (direction == 'S')
		p->angle = 3 * M_PI / 2;
	else if (direction == 'E')
		p->angle = 0;
	else if (direction == 'W')
		p->angle = M_PI;
}

int	found_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_one_player(t_player *p)
{
	int	count;
	int	i;
	int	j;
	int x_pos;
	int y_pos;

	count = 0;
	i = 0;
	j = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (found_player(p->map[i][j]))
			{
				char *n_pos = ft_strchr(p->map[i], 'N');
				char *s_pos = ft_strchr(p->map[i], 'S');
				char *e_pos = ft_strchr(p->map[i], 'E');
				char *w_pos = ft_strchr(p->map[i], 'W');
				if (n_pos)
					x_pos = n_pos - p->map[i];
				if (s_pos)
					x_pos = s_pos - p->map[i];
				if (e_pos)
					x_pos = e_pos - p->map[i];
				if (w_pos)
					x_pos = w_pos - p->map[i];
				y_pos = j;
				p->x = (x_pos * TILE_SIZE) + (TILE_SIZE / 2);
				p->y = (y_pos * TILE_SIZE) + (TILE_SIZE / 2);
				update_player(p, p->map[i][j]);
				p->map[i][j] = '0';
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_putstr_fd("nbr player = 1\n", 2), -1);
	return (0);
}
