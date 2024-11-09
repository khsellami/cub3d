/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/09 18:13:44 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_game(t_player *p)
{
	p->mlx = mlx_init();
	if (!p->mlx)
		return (1);
	init_textures(p);
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
	clear_image(p);
	cast_all_rays(p);
	mlx_put_image_to_window(p->mlx, p->window, p->img, 0, 0);
	return (0);
}

void	stock_dim_map(t_player *p)
{
	int	i = 0;
	int	j = 0;

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
	if (ft_read_map(av, &p) == -1)
		return (1);
	if (check_one_player(&p) == -1)
		return (1);
	stock_dim_map(&p);
	if (!valid_map(&p))
		return (1);
	if (create_game(&p))
		return (1);
	mlx_hook(p.window, 2, 0, key_eshap, &p);
	mlx_hook(p.window, 17, 0, close_window, &p);
	mlx_loop(p.mlx);
	return (0);
}
