/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:47:43 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 19:53:12 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// int render3d(void *param)
// {
//     t_game *game;
//     int num_rays;
//     double rayAngle;
//     int x;
//     double rayPosX;
//     double rayPosY;
//     double rayDirX;
//     double rayDirY;
//     double distanceToWall;
//     int hit;

//     game = (t_game *)param;
//     mlx_clear_window(game->mlx, game->window);
//     //nombre rayons
//     num_rays = SCREEN_WIDTH;
//     // Calculer les rayons
//     x = 0;
//     while (x < num_rays)
//     {
//         //calculer l'angle rayon
//         rayAngle = game->player.angle + atan(tan(FOV / 2 * (M_PI / 180)) * (2.0 * x / num_rays - 1));
//         // calculer position rayon
//         rayPosX = game->player.x;
//         rayPosY = game->player.y;
//         // calculer direction du rayon
//         rayDirX = cos(rayAngle);
//         rayDirY = sin(rayAngle);
//         // Longueur du rayon
//         distanceToWall = 0;
//         hit = 0;
//         // Avancer le rayon jusqu'à toucher un mur
//         while (!hit && distanceToWall < 100)
//         { 
//             // Limite de distance
//             distanceToWall += 0.1;// Avance le rayon
//             // Calcul de la position dans la grille
//             int gridX = (int)(rayPosX + rayDirX * distanceToWall);
//             int gridY = (int)(rayPosY + rayDirY * distanceToWall);
//             // Simuler un mur (vous pouvez remplacer cela par votre logique de carte)
//             if (gridX < 0 || gridX >= SCREEN_WIDTH || gridY < 0 || gridY >= SCREEN_HEIGHT) {
//                 hit = 1; // Sortir de l'écran
//             }
//             else if (gridY % 100 == 0 && gridX % 100 == 0)
//                 // Supposons que les murs sont aux coordonnées multiples de 100
//                 hit = 1; // Collision avec un mur
//         }
//         // Dessiner le rayon jusqu'à la distance trouvée
//         int i = 0;
//         while (i < distanceToWall)
//         {
//             int pixelX = (int)(rayPosX + rayDirX * i);
//             int pixelY = (int)(rayPosY + rayDirY * i);
//             // Utilisez put_pixel ou une autre méthode pour dessiner
//             if (pixelX >= 0 && pixelX < SCREEN_WIDTH && pixelY >= 0 && pixelY < SCREEN_HEIGHT) {
//                 mlx_pixel_put(game->mlx, game->window, pixelX, pixelY, 0xFFFFFF); // Couleur blanche pour le rayon
//             }
//             i++;
//         }
//         x++;
//     }
//     return (0);
// }
float	get_h_inter(t_game *mlx, float angl)	// get the horizontal intersection
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(mlx->player.y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->player.x + (h_y - mlx->player.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->player.x, 2) + pow(h_y - mlx->player.y, 2))); // get the distance
}

float	get_v_inter(t_game *mlx, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(mlx->player.x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = mlx->player.y + (v_x - mlx->player.x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - mlx->player.x, 2) + pow(v_y - mlx->player.y, 2))); // get the distance
}

void	cast_rays(t_game *mlx)	// cast the rays
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->ray.ray_ngl = mlx->player.angle - (mlx->player.fov_rd / 2); // the start angle
	while (ray < SCREEN_WIDTH) // loop for the rays
	{
		mlx->ray.flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray.ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray.ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray.distance = v_inter; // get the distance
		else
		{
			mlx->ray.distance = h_inter; // get the distance
			mlx->ray.flag = 1; // flag for the wall
		}
		render_wall(mlx, ray); // render the wall
		ray++; // next ray
		mlx->ray.ray_ngl += (mlx->player.fov_rd / SCREEN_WIDTH); // next angle
	}
}

void	rotate_player(t_game *mlx, int i)	// rotate the player
{
	if (i == 1)
	{
		mlx->player.angle += ROTATION_SPEED; // rotate right
		if (mlx->player.angle > 2 * M_PI)
			mlx->player.angle -= 2 * M_PI;
	}
	else
	{
		mlx->player.angle -= ROTATION_SPEED; // rotate left
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * M_PI;
	}
}

void	move_player(t_game *mlx, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(mlx->player.x + move_x); // get the new x position
	new_y = roundf(mlx->player.y + move_y); // get the new y position
	map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	map_grid_y = (new_y / TILE_SIZE); // get the y position in the map
	if (mlx->map[map_grid_y][map_grid_x] != '1' && \
	(mlx->map[map_grid_y][mlx->player.x / TILE_SIZE] != '1' && \
	mlx->map[mlx->player.y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		mlx->player.x = new_x; // move the player
		mlx->player.y = new_y; // move the player
	}
}

void	hook(t_game *mlx, double move_x, double move_y)	// hook the player
{
	if (mlx->player.rot == 1) //rotate right
		rotate_player(mlx, 1);
	if (mlx->player.rot == -1) //rotate left
		rotate_player(mlx, 0);
	if (mlx->player.l_r == 1) //move right
	{
		move_x = -sin(mlx->player.angle) * PLAYER_SPEED;
		move_y = cos(mlx->player.angle) * PLAYER_SPEED;
	}
	if (mlx->player.l_r == -1) //move left
	{
		move_x = sin(mlx->player.angle) * PLAYER_SPEED;
		move_y = -cos(mlx->player.angle) * PLAYER_SPEED;
	}
	if (mlx->player.u_d == 1) //move up
	{
		move_x = cos(mlx->player.angle) * PLAYER_SPEED;
		move_y = sin(mlx->player.angle) * PLAYER_SPEED;
	}
	if (mlx->player.u_d == -1) //move down
	{
		move_x = -cos(mlx->player.angle) * PLAYER_SPEED;
		move_y = -sin(mlx->player.angle) * PLAYER_SPEED;
	}
	move_player(mlx, move_x, move_y); // move the player
}

int	wall_hit(float x, float y, t_game *mlx)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); // get the x position in the map
	y_m = floor (y / TILE_SIZE); // get the y position in the map
	if ((y_m >= mlx->h_map || x_m >= mlx->w_map))
		return (0);
	if (mlx->map[y_m] && x_m <= (int)ft_strlen(mlx->map[y_m]))
		if (mlx->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}


void	render_wall(t_game *mlx, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->ray.distance *= cos(nor_angle(mlx->ray.ray_ngl - mlx->player.angle)); // fix the fisheye
	wall_h = (TILE_SIZE / mlx->ray.distance) * ((SCREEN_WIDTH / 2) / tan(mlx->player.fov_rd / 2)); // get the wall height
	b_pix = (SCREEN_WIDTH / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (SCREEN_WIDTH / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > SCREEN_HEIGHT) // check the bottom pixel
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}

void	draw_wall(t_game *mlx, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(mlx, mlx->ray.flag);
	while (t_pix < b_pix)
		my_mlx_pixel_put(mlx, ray, t_pix++, color);
}

int	get_color(t_game *mlx, int flag)	// get the color of the wall
{
	mlx->ray.ray_ngl = nor_angle(mlx->ray.ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray.ray_ngl > M_PI / 2 && mlx->ray.ray_ngl < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (mlx->ray.ray_ngl > 0 && mlx->ray.ray_ngl < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_floor_ceiling(t_game *mlx, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	// int		c;

	i = b_pix;
	while (i < SCREEN_HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF); // ceiling
}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}


void	my_mlx_pixel_put(t_game *mlx, int x, int y, int color)	// put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	// mlx_put_pixel(mlx->img, x, y, color); // put the pixel
}
// void	my_mlx_pixel_put(t_game *mlx, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = mlx->addr + \
// 		(y * mlx->line_len + x * (mlx->bits_per_px / 8));
// 	*(unsigned int *)dst = color;
// }




int	render3d(void *param)	// game loop
{
	t_game	*game;

	game = param;	// cast to the mlx structure
	// mlx_delete_image(game->mlx, game->img);	// delete the image
	// mlx_destroy_image(game->mlx, game->img);
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);	// create new image
	hook(game, 0, 0); // hook the player
	cast_rays(game);	// cast the rays
	// mlx_image_to_window(game->mlx, game->img, 0, 0); // put the image to the window
    mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0); 
    return (0);
}