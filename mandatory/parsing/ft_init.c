/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:55:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/21 14:48:27 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_player(t_player *p)
{
	p->x = SW / 2;
	p->y = SH / 2;
	p->angle = 0;
	p->rotationangle = M_PI / 3;
	p->movespeed = 10;
	p->rotationspeed = 5 * (M_PI / 180);
}

void	init_rays(t_player *p)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		p->rays[i].horizontal_distance = 0;
		p->rays[i].vertical_distance = 0;
		p->rays[i].distance = 0.0;
		p->rays[i].angle = 0.0;
		p->rays[i].israyfacingdown = 0;
		p->rays[i].israyfacingup = 0;
		p->rays[i].israyfacingright = 0;
		p->rays[i].israyfacingleft = 0;
		i++;
	}
}

int	init(t_player *p)
{
	init_player(p);
	init_rays(p);
	p->mlx = NULL;
	p->window = NULL;
	p->img = malloc(sizeof(t_img));
	p->img->img = NULL;
	p->img->data = NULL;
	p->img->bpp = 0;
	p->img->line_length = 0;
	p->img->endian = 0;
	p->no = NULL;
	p->so = NULL;
	p->ea = NULL;
	p->we = NULL;
	p->floor_color = -1;
	p->ciel_color = -1;
	p->map = NULL;
	return (0);
}
