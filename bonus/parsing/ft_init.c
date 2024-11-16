/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:55:20 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/16 14:03:41 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	init_player(t_player *p)
{
	p->x = SW / 2;
	p->y = SH / 2;
	p->angle = 0;
	p->rotationangle = M_PI / 3;
	p->movespeed = 25;
	p->rotationspeed = 2 * (M_PI / 180);
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
	p->img = NULL;
	p->img_data = NULL;
	p->bpp = 0;
	p->line_length = 0;
	p->endian = 0;
	p->no = NULL;
	p->so = NULL;
	p->ea = NULL;
	p->we = NULL;
	p->floor_color = -1;
	p->ciel_color = -1;
	p->map = NULL;
	p->last_mouse_x = 0;
	p->last_mouse_y = 0;
	p->is_animating = 0;
	p->sprite_frames[0].img = NULL;
	p->scale_factor = 1.5;
	return (0);
}
