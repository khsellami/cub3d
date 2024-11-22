/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/22 12:40:14 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	loop_hook(t_player *player)
{
	cast_all_rays(player);
	draw_pistol(player);
	draw_map(player);
	mlx_put_image_to_window(player->mlx, player->window, \
	player->img->img, 0, 0);
	return (0);
}

int	create_game(t_player *p)
{
	p->mlx = mlx_init();
	if (!p->mlx)
		return (1);
	init_textures(p);
	init_player_sprite(p);
	p->window = mlx_new_window(p->mlx, SW, SH, "Cub3D");
	if (!p->window)
		return (1);
	p->img->img = mlx_new_image(p->mlx, SW, SH);
	if (!p->img->img)
	{
		mlx_destroy_window(p->mlx, p->window);
		return (1);
	}
	p->img->data = mlx_get_data_addr(p->img->img, &p->img->bpp, \
	&p->img->line_length, &p->img->endian);
	if (!p->img->data)
	{
		mlx_destroy_image(p->mlx, p->img->img);
		mlx_destroy_window(p->mlx, p->window);
		return (1);
	}
	cast_all_rays(p);
	mlx_put_image_to_window(p->mlx, p->window, p->img->img, 0, 0);
	return (0);
}

void	stock_dim_map(t_player *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	p->map_row = 0;
	p->map_col = 0;
	while (p->map[i])
		i++;
	if (p->map[0])
		j = ft_strlen(p->map[0]);
	p->map_row = i;
	p->map_col = j;
}

int	main(int ac, char **av)
{
	t_player	p;

	if (ac != 2)
		return (ft_putstr_fd("ERROR\nNbr args invalide\n", 2), 1);
	if (checkfilename(av[1]) == -1)
		return (ft_putstr_fd("ERROR\nExtension must be .cub\n", 2), 1);
	if (init(&p) == -1)
		return (ft_putstr_fd("ERROR\nProblem in init data\n", 2), 1);
	if (parse_colors_textures(av, &p) == -1)
		return (free(p.img), ft_putstr_fd(TEXT1, 2), 1);
	if (check_clr_txt(&p))
		return (free(p.img), ft_putstr_fd(TEXT2, 2), 1);
	if (ft_read_map(av, &p) == -1 || check_one_player(&p) == -1)
		return (free(p.img), ft_putstr_fd("ERROR\nread map\n", 2), 1);
	stock_dim_map(&p);
	if (!valid_map(&p))
		return (free(p.img), ft_putstr_fd("ERROR\nInvalid map\n", 2), 1);
	if (create_game(&p))
		return (free(p.img), 1);
	mlx_loop_hook(p.mlx, loop_hook, &p);
	mlx_hook(p.window, 2, 0, key_eshap, &p);
	mlx_hook(p.window, 6, 0, mouse_motion, &p);
	mlx_hook(p.window, 17, 0, close_window, &p);
	mlx_loop(p.mlx);
	return (free(p.img), 0);
}
