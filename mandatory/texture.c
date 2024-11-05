/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:33:24 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/05 15:25:53 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture(t_player *player, char *path, t_img *texture)
{
	if (!player || !player->mlx || !texture || !path)
		return 1;
	if (access(path, F_OK) == -1)
	{
		printf("Erreur: Le fichier %s n'existe pas.\n", path);
		return (1);
	}
	texture->img = mlx_xpm_file_to_image(player->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->data)
		return (1);
	printf("Image texture  chargée avec succès: %s\n", path);
	return (0);
}

void	init_textures(t_player *player)
{
	if (load_texture(player, "./wall_north.xpm", &player->no_img) ||
		load_texture(player, "./wall_south.xpm", &player->so_img) ||
		load_texture(player, "./wall_east.xpm", &player->ea_img) ||
		load_texture(player, "./wall_west.xpm", &player->we_img))
		{
		printf("Erreur: Échec du chargement des textures\n");
		exit(EXIT_FAILURE);
	}
}

t_img	*get_texture(t_player *player, int ray_id)
{
	int	texture_index;

	if (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance)
	{
		if (cos(player->rays[ray_id].angle) > 0)
			texture_index = 2;
		else
			texture_index = 3;
	}
	else
	{
		if (sin(player->rays[ray_id].angle) > 0)
			texture_index = 0;
		else
			texture_index = 1;
	}
	if (texture_index == 0)
		return (&player->no_img);
	else if (texture_index == 1)
		return (&player->so_img);
	else if (texture_index == 2)
		return (&player->ea_img);
	else 
		return (&player->we_img);
}
int	calculate_texture_x(t_player *player, int ray_id, t_img *texture)
{
	if(player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance)
		return ((int)fmod(player->rays[ray_id].vert_y, TILE_SIZE) * texture->width / TILE_SIZE);
	else
		return ((int)fmod(player->rays[ray_id].horz_x, TILE_SIZE) * texture->width / TILE_SIZE);
}
// int	calculate_texture_x(t_player *player, int ray_id, t_img *texture)
// {
// 	double	wall_hit;

// 	if (player->rays[ray_id].vertical_distance < player->rays[ray_id].horizontal_distance)
// 		wall_hit = fmod(player->rays[ray_id].vert_y, TILE_SIZE);
// 	else
// 		wall_hit = fmod(player->rays[ray_id].horz_x, TILE_SIZE);
// 	return ((int)(wall_hit * texture->width / TILE_SIZE));
// }
