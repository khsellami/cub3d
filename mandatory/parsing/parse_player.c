/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:01:31 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/18 15:55:36 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	update_player(t_player *p, char direction)
{
	if (direction == 'N')
		p->rotationangle = M_PI / 2;
	else if (direction == 'S')
		p->rotationangle = 3 * M_PI / 2;
	else if (direction == 'E')
		p->rotationangle = 0;
	else if (direction == 'W')
		p->rotationangle = M_PI;
}

int	found_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	update_player_position(t_player *p, t_data *data, int i)
{
	data->n_pos = ft_strchr(p->map[i], 'N');
	data->s_pos = ft_strchr(p->map[i], 'S');
	data->e_pos = ft_strchr(p->map[i], 'E');
	data->w_pos = ft_strchr(p->map[i], 'W');
	if (data->n_pos)
		data->x_pos = data->n_pos - p->map[i];
	else if (data->s_pos)
		data->x_pos = data->s_pos - p->map[i];
	else if (data->e_pos)
		data->x_pos = data->e_pos - p->map[i];
	else if (data->w_pos)
		data->x_pos = data->w_pos - p->map[i];
	p->x = (data->x_pos * TILE_SIZE) + (TILE_SIZE / 2);
	p->y = (i * TILE_SIZE) + (TILE_SIZE / 2);
	update_player(p, p->map[i][data->x_pos]);
	p->map[i][data->x_pos] = '0';
}

int	check_one_player(t_player *p)
{
	t_data	data;
	int		i;
	int		j;

	data.count = 0;
	i = 0;
	data.x_pos = 0;
	data.y_pos = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (found_player(p->map[i][j]))
			{
				update_player_position(p, &data, i);
				data.count++;
			}
			j++;
		}
		i++;
	}
	if (data.count != 1)
		return (ft_putstr_fd("\nNbr player = 1\n", 2), -1);
	return (0);
}
