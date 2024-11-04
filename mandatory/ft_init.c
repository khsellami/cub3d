/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:03:51 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 22:01:22 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init(t_player *p)
{
	int	i;

	i = 0;
	p->x = SW / 2;
	p->y = SH / 2;
	p->angle = 0;
	p->radius = 3;
	p->rotationAngle = M_PI / 3;
	p->moveSpeed = 25;
	p->rotationSpeed = 2 * (M_PI / 180);
	p->mlx = NULL;
	p->window = NULL;
	p->img = NULL;
	p->img_data = NULL;
	p->bpp = 0;
	p->line_length = 0;
	p->endian = 0;
	p->no = NULL;
	p->so = NULL;
	p->ea = NULL;
	p->we = NULL;
	p->floor_color = 0;
	p->ciel_color = 0;
	p->map = NULL;
	while (i < NUM_RAYS)
	{
		p->rays[i].horizontal_distance = 0;
		p->rays[i].vertical_distance = 0;
		p->rays[i].distance = 0.0;
		p->rays[i].angle = 0.0;
		i++;
	}
}