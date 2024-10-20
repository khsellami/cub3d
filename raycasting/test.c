/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:47:43 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 16:09:23 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int render3d(void *param)
{
    t_game *game;
    int num_rays;
    double rayAngle;
    int x;
    double rayPosX;
    double rayPosY;
    double rayDirX;
    double rayDirY;
    double distanceToWall;
    int hit;

    game = (t_game *)param;
    mlx_clear_window(game->mlx, game->window);
    //nombre rayons
    num_rays = SCREEN_WIDTH;
    // Calculer les rayons
    x = 0;
    while (x < num_rays)
    {
        //calculer l'angle rayon
        rayAngle = game->player.angle + atan(tan(FOV / 2 * (M_PI / 180)) * (2.0 * x / num_rays - 1));
        // calculer position rayon
        rayPosX = game->player.x;
        rayPosY = game->player.y;
        // calculer direction du rayon
        rayDirX = cos(rayAngle);
        rayDirY = sin(rayAngle);
        // Longueur du rayon
        distanceToWall = 0;
        hit = 0;
        // Avancer le rayon jusqu'à toucher un mur
        while (!hit && distanceToWall < 100)
        { 
            // Limite de distance
            distanceToWall += 0.1;// Avance le rayon
            // Calcul de la position dans la grille
            int gridX = (int)(rayPosX + rayDirX * distanceToWall);
            int gridY = (int)(rayPosY + rayDirY * distanceToWall);
            // Simuler un mur (vous pouvez remplacer cela par votre logique de carte)
            if (gridX < 0 || gridX >= SCREEN_WIDTH || gridY < 0 || gridY >= SCREEN_HEIGHT) {
                hit = 1; // Sortir de l'écran
            }
            else if (gridY % 100 == 0 && gridX % 100 == 0)
                // Supposons que les murs sont aux coordonnées multiples de 100
                hit = 1; // Collision avec un mur
        }
        // Dessiner le rayon jusqu'à la distance trouvée
        int i = 0;
        while (i < distanceToWall)
        {
            int pixelX = (int)(rayPosX + rayDirX * i);
            int pixelY = (int)(rayPosY + rayDirY * i);
            // Utilisez put_pixel ou une autre méthode pour dessiner
            if (pixelX >= 0 && pixelX < SCREEN_WIDTH && pixelY >= 0 && pixelY < SCREEN_HEIGHT) {
                mlx_pixel_put(game->mlx, game->window, pixelX, pixelY, 0xFFFFFF); // Couleur blanche pour le rayon
            }
            i++;
        }
        x++;
    }
    return (0);
}

