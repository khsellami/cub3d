/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/09 21:57:00 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	loop_hook(t_player *player)
{
	clear_image(player);
	cast_all_rays(player);
	draw_pistol(player);
	draw_map(player);
	mlx_put_image_to_window(player->mlx, player->window, player->img, 0, 0);
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
	p->img = mlx_new_image(p->mlx, SW, SH);
	if (!p->img)
		return (1);
	p->img_data = mlx_get_data_addr(p->img, &p->bpp, \
	&p->line_length, &p->endian);
	if (!p->img_data)
		return (1);
	mlx_put_image_to_window(p->mlx, p->window, p->img, 0, 0);
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
		return (ft_putstr_fd("Nbr args invalide\n", 2), 1);
	if (checkfilename(av[1]) == -1)
		return (ft_putstr_fd("Extension must be .cub\n", 2), 1);
	if (init(&p) == -1)
		return (ft_putstr_fd("Problem when initialize our data\n", 2), 1);
	if (parse_colors_textures(av, &p) == -1)
		return (ft_putstr_fd("Problem when stock colors and textures\n", 2), 1);
	if (check_clr_txt(&p))
		return (ft_putstr_fd("No textures provided\n", 2), 1);
	if (ft_read_map(av, &p) == -1 || check_one_player(&p) == -1)
		return (1);
	stock_dim_map(&p);
	if (!valid_map(&p))
		return (1);
	if (create_game(&p))
		return (1);
	mlx_loop_hook(p.mlx, loop_hook, &p);
	mlx_hook(p.window, 2, 0, key_eshap, &p);
	mlx_hook(p.window, 6, 0, mouse_motion, &p);
	mlx_hook(p.window, 17, 0, close_window, &p);
	mlx_loop(p.mlx);
	return (0);
}
