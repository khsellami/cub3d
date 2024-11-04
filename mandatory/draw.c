/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:42:37 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 21:35:43 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (y < SH / 2)
	{
		x = 0;
		while (x < SW)
		{
			put_pixel(player, x, y, player->ciel_color);
			x++;
		}
		y++;
	}
	y = SH / 2;
	while (y < SH)
	{
		x = 0;
		while (x < SW)
		{
			put_pixel(player, x, y, player->floor_color);
			x++;
		}
		y++;
	}
}

void	calculate_wall_properties(t_player *player, int ray_id, double distance, t_data *data)
{
	double	proj;

	data->angle_diff = player->rays[ray_id].angle - player->rotationAngle;
	data->corrected_distance = distance * cos(data->angle_diff);
	if (data->corrected_distance <= 0)
	{
		data->wall_height = 0;
		return ;
	}
	proj = (SW / 2) / tan(FOV_ANGLE / 2);
	double projectedWallHeight = (TILE_SIZE / data->corrected_distance) * proj;
	data->wall_height = (int)projectedWallHeight;
	if (data->wall_height < 0)
		 data->wall_height = 0;
	data->wall_top = (SH / 2) - (data->wall_height / 2);
	if (data->wall_top < 0)
		data->wall_top = 0;
	data->wall_bottom = (SH / 2) + (data->wall_height / 2);
	if (data->wall_bottom > SH)
		data->wall_bottom = SH;
	data->x_pos = ray_id;
}

void	render_wall_slice(t_player *player, t_data *data, t_img *texture)
{
	int	color;
	int	d;
	int	y;

	if (data->wall_height <= 0)
	{
		printf("Erreur: wall_height %d est invalide\n", data->wall_height);
		return ;
	}
	if (texture->height <= 0)
	{
		printf("Erreur: texture height %d est invalide\n", texture->height);
		return ;
	}
	y = data->wall_top;
	while (y < data->wall_bottom)
	{
		d = (y - data->wall_top) * texture->height / data->wall_height;
		data->texture_y = abs(d % texture->height);
		if (data->texture_y < 0 || data->texture_y >= texture->height)
		{
			printf("Erreur: texture_y %d est hors limites\n", data->texture_y);
			return ;
		}
		if (data->texture_x < 0 || data->texture_x >= texture->width)
		{
			printf("Erreur: texture_x %d est hors limites\n", data->texture_x);
			return ;
		}
		color = *(int *)(texture->data + (data->texture_y * texture->line_length + data->texture_x * (texture->bpp / 8)));
		if (color == 0)
			color = 0x00FF00;
		put_pixel(player, data->x_pos, y, color);
		y++;
	}
}

void	render_3d_wall_slice(t_player *player, int ray_id, double distance)
{
	t_data	data;
	t_img	*texture;

	calculate_wall_properties(player, ray_id, distance, &data);
	texture = get_texture(player, ray_id);
	if (!texture || !texture->img)
	{
		printf("Erreur: La texture %d n'est pas chargée correctement\n", data.texture_index);
		return ;
	}
	data.texture_x = calculate_texture_x(player, ray_id, texture);
	if (data.texture_x < 0 || data.texture_x >= texture->width)
	{
		printf("Erreur: texture_x %d est hors limites\n", data.texture_x);
		return ;
	}
	render_wall_slice(player, &data, texture);
}
