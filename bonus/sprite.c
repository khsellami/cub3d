/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:49:27 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 20:30:53 by kahmada          ###   ########.fr       */
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
    int x, y;
    int screen_x, screen_y;
    char *pixel;

    // Get the center position of where you want to place the sprite
    int draw_x = (int)(player->pos_x) - (player->sprite_img.width / 2);
    int draw_y = (int)(player->pos_y) - (player->sprite_img.height / 2);

    // Iterate over the sprite’s pixels
    for (y = 0; y < player->sprite_img.height; y++)
    {
        for (x = 0; x < player->sprite_img.width; x++)
        {
            // Calculate the screen position for this pixel
            screen_x = draw_x + x;
            screen_y = draw_y + y;

            // Get the pixel color from the sprite data
            pixel = player->sprite_img.data + (y * player->sprite_img.line_length + x * (player->sprite_img.bpp / 8));
            int color = *(unsigned int *)pixel;

            // If color is not transparent, put it on the screen
            if (color != 0) // Assuming 0xFF000000 is transparent
                put_pixel(player, screen_x, screen_y, color);
        }
    }
}
void draw_pistol(t_player *player)
{
    int x, y;
    int screen_x, screen_y;
    char *pixel;

    // Center the pistol image and adjust vertically if needed
    int draw_x = (SW / 2) - (player->sprite_img.width); // Adjust for larger size
    int draw_y = (SH * 0.75) - (player->sprite_img.height); // Adjust for larger size

    // Draw each pixel in the pistol sprite as a 2x2 block
    for (y = 0; y < player->sprite_img.height; y++)
    {
        for (x = 0; x < player->sprite_img.width; x++)
        {
            screen_x = draw_x + x * 2;  // Scale width
            screen_y = draw_y + y * 2;  // Scale height

            // Get the color of the pixel from the sprite image
            pixel = player->sprite_img.data + (y * player->sprite_img.line_length + x * (player->sprite_img.bpp / 8));
            unsigned int color = *(unsigned int *)pixel;

            // Draw a 2x2 block if the pixel is not transparent
            if (color != 0xFF000000)
            {
                put_pixel(player, screen_x, screen_y, color);
                put_pixel(player, screen_x + 1, screen_y, color);
                put_pixel(player, screen_x, screen_y + 1, color);
                put_pixel(player, screen_x + 1, screen_y + 1, color);
            }
        }
    }
}









