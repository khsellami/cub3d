/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:49:27 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 18:51:20 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"
#include "mlx.h" // Include your necessary headers
int load_sprite(t_player *player, char *path)
{
    // Check for valid inputs
    if (!player || !player->mlx || !path)
        return 1;

    // Check if the sprite file exists
    if (access(path, F_OK) == -1)
    {
        printf("Erreur: Le fichier %s n'existe pas.\n", path);
        return 1;
    }

    // Load the sprite image
    player->sprite_img.img = mlx_xpm_file_to_image(player->mlx, path, &player->sprite_img.width, &player->sprite_img.height);
    if (!player->sprite_img.img)
    {
        printf("Erreur: Échec du chargement de l'image du sprite\n");
        return 1;
    }

    // Get the image data
    player->sprite_img.data = mlx_get_data_addr(player->sprite_img.img, &player->sprite_img.bpp, &player->sprite_img.line_length, &player->sprite_img.endian);
    if (!player->sprite_img.data)
    {
        printf("Erreur: Échec de l'obtention des données de l'image du sprite\n");
        return 1;
    }

    printf("Image du sprite chargée avec succès: %s\n", path);
    return 0;
}

void init_player_sprite(t_player *player)
{
    if (load_sprite(player, "./pistolet.xpm"))
    {
        printf("Erreur: Échec du chargement du sprite du joueur\n");
        exit(EXIT_FAILURE);
    }
}

void draw_player(t_player *player)
{
    int x_center = (int)(player->pos_x); // Assuming pos_x and pos_y are the player's position
    int y_center = (int)(player->pos_y);
    
    // Draw the sprite texture at the player's position
    int start_x = x_center - (player->sprite_img.width / 2);
    int start_y = y_center - (player->sprite_img.height / 2);
    
    // Loop through each pixel of the sprite
    for (int y = 0; y < player->sprite_img.height; y++)
    {
        for (int x = 0; x < player->sprite_img.width; x++)
        {
            // Get the color of the pixel from the sprite texture
            int color = ((int*)(player->sprite_img.data))[(y * player->sprite_img.line_length / 4) + x]; // Adjust line length for color retrieval

            // Check if the pixel is not transparent (assuming 0 is transparent)
            if (color != 0) // Replace with your transparency check if needed
            {
                put_pixel(player, start_x + x, start_y + y, color);
            }
        }
    }
}




