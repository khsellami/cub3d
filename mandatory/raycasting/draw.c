/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:42:37 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/21 16:14:06 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	calculate_wall_properties(t_player *player, int ray_id, \
double distance, t_data *data)
{
	double	proj;

	data->angle_diff = player->rays[ray_id].angle - player->rotationangle;
	data->corrected_distance = distance * cos(data->angle_diff);
	if (data->corrected_distance <= 0)
		data->wall_height = 0;
	proj = (SW / 2) / tan(FOV_ANGLE / 2);
	data->wall_height = (TILE_SIZE / data->corrected_distance) * proj;
	data->wall_top = (SH / 2) - (data->wall_height / 2);
	data->wall_bottom = (SH / 2) + (data->wall_height / 2);
	if (data->wall_bottom >= SH)
		data->wall_bottom = SH;
	data->x_pos = ray_id;
}

void	render_wall_slice(t_player *player, t_data *data, t_img *texture)
{
	int	color;
	int	d;
	int	y;

	if (data->wall_height == 0)
		return ;
	if (texture->height <= 0)
		return ;
	y = data->wall_top;
	while (y < data->wall_bottom)
	{
		d = (y - data->wall_top) * texture->height / data->wall_height;
		data->texture_y = d % texture->height;
		if (data->texture_y < 0 || data->texture_y >= texture->height)
			return ;
		color = *(unsigned int *)(texture->data + (data->texture_y * \
		texture->line_length + data->texture_x * (texture->bpp / 8)));
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

	data.wall_height = 0;
	calculate_wall_properties(player, ray_id, distance, &data);
	texture = get_texture(player, ray_id);
	if (!texture || !texture->img)
		return ;
	data.texture_x = calculate_texture_x(player, ray_id, texture);
	if (data.texture_x < 0 || data.texture_x >= texture->width)
		return ;
	render_wall_slice(player, &data, texture);
}
