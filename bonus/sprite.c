/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:51:22 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/16 14:05:40 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	load_sprite(t_player *player, char *path, int frame_index)
{
	if (!player || !player->mlx || !path || frame_index >= NUM_FRAMES)
		return (1);
	player->sprite_frames[frame_index].img = \
	mlx_xpm_file_to_image(player->mlx, path, \
	&player->sprite_frames[frame_index].width, \
	&player->sprite_frames[frame_index].height);
	if (!player->sprite_frames[frame_index].img)
	{
		printf("Erreur: Échec du chargement de l'image du sprite %s\n", path);
		return (1);
	}
	player->sprite_frames[frame_index].data = \
	mlx_get_data_addr(player->sprite_frames[frame_index].img, \
	&player->sprite_frames[frame_index].bpp, \
	&player->sprite_frames[frame_index].line_length, \
	&player->sprite_frames[frame_index].endian);
	if (!player->sprite_frames[frame_index].data)
		return (1);
	return (0);
}

void	init_player_sprite(t_player *player)
{
	int		i;
	char	*paths[NUM_FRAMES];

	paths[0] = "./sp/pis0.xpm";
	paths[1] = "./sp/pis1.xpm";
	paths[2] = "./sp/pis2.xpm";
	paths[3] = "./sp/pis3.xpm";
	paths[4] = "./sp/pis4.xpm";
	paths[5] = "./sp/pis5.xpm";
	paths[6] = "./sp/pis6.xpm";
	paths[7] = "./sp/pis7.xpm";
	paths[8] = "./sp/pis8.xpm";
	i = 0;
	while (i < NUM_FRAMES)
	{
		if (load_sprite(player, paths[i], i) != 0)
		{
			printf("ERROR: Échec du chargement de l'image %s\n", paths[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	player->current_frame = 0;
}

void	update_animation_frame(t_player *player)
{
	if (player->is_animating)
		player->current_frame = (player->current_frame + 1) % NUM_FRAMES;
	else
		player->current_frame = 0;
}

void	draw_scaled_pixel(t_player *player, int screen_x, \
int screen_y, unsigned int color)
{
	put_pixel(player, screen_x, screen_y, color);
	if (player->scale_factor > 1)
	{
		put_pixel(player, screen_x + 1, screen_y, color);
		put_pixel(player, screen_x, screen_y + 1, color);
		put_pixel(player, screen_x + 1, screen_y + 1, color);
	}
}

void	draw_pistol(t_player *player)
{
	t_img	*current_frame;
	t_data	d;

	current_frame = &player->sprite_frames[player->current_frame];
	d.draw_x = (SW / 2) - (current_frame->width);
	d.draw_y = (SH * 0.5) - (current_frame->height);
	d.y = 0;
	while (d.y < current_frame->height)
	{
		d.x = 0;
		while (d.x < current_frame->width)
		{
			d.screen_x = d.draw_x + d.x * player->scale_factor;
			d.screen_y = d.draw_y + d.y * player->scale_factor;
			d.pixel = current_frame->data + \
			(d.y * current_frame->line_length \
			+ d.x * (current_frame->bpp / 8));
			d.color = *(unsigned int *)d.pixel;
			if ((unsigned int)d.color != 0xFF000000)
				draw_scaled_pixel(player, d.screen_x, d.screen_y, d.color);
			d.x++;
		}
		d.y++;
	}
	update_animation_frame(player);
}
