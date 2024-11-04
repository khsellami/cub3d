/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:01:31 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 15:59:31 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(t_player *p, int x, int y, char direction)
{
	p->x = (double)x;
	p->y = (double)y;
	if (direction == 'N')
		p->angle = M_PI / 2;
	else if (direction == 'S')
		p->angle = 3 * M_PI / 2;
	else if (direction == 'E')
		p->angle = 0;
	else if (direction == 'W')
		p->angle = M_PI;
}

int	check_one_player(t_player *p)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (p->map[i])
	{
		j = 0;
		while(p->map[i][j])
		{
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S' || p->map[i][j] == 'E' || p->map[i][j] == 'W')
			{
				// init_player(p, i, j, p->map[i][j]);
				p->map[i][j] = '0';
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_putstr_fd("nbr player = 1\n", 2),-1);
	return (0);
}
