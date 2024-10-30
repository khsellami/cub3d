/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:23:35 by kahmada           #+#    #+#             */
/*   Updated: 2024/10/29 11:24:32 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void *get_texture_data(t_texture *texture)
{
    int bpp;
    int line_length;
    int endian;
    void *addr;

    addr = mlx_get_data_addr(texture, &bpp, &line_length, &endian);
    if (!addr)
    {
        write(2, "Error getting image data\n", 25);
        exit(1);
    }
    return addr;
}

int load_texture(t_player *player, char *path, t_img *texture)
{
    if (!player || !player->mlx || !texture || !path)
        return 1;
    if (access(path, F_OK) == -1)
    {
        printf("Erreur: Le fichier %s n'existe pas.\n", path);
        return 1;
    }
    texture->img = mlx_xpm_file_to_image(player->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        return 1;
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
    if (!texture->data)
        return 1;
    printf("Image texture  chargée avec succès: %s\n", path);
    return 0;
}

void init_textures(t_player *player)
{
    if (load_texture(player, "./wall_north.xpm", &player->no_img) ||
        load_texture(player, "./wall_south.xpm", &player->so_img) ||
        load_texture(player, "./wall_east.xpm", &player->ea_img) ||
        load_texture(player, "./wall_west.xpm", &player->we_img)) {
        printf("Erreur: Échec du chargement des textures\n");
        exit(EXIT_FAILURE);
    }
}