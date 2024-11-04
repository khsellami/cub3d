/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:49:13 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/04 21:37:29 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	t_player	p;

	if (ac != 2)
		return (ft_putstr_fd("USAGE: .cub3D <name_map.cub>\n", 2), 1);
	if (checkfilename(av[1]) == -1)
		return (ft_putstr_fd("Invalid extension file name\n", 2), 1);
	init(&p);
	if (parse_colors_textures(ac , av , &p) == -1)
		return (1);
	if (check_clr_txt(&p))
		return (ft_putstr_fd("No colors or textures\n", 2),1);
	if (ft_parsing(ac , av, &p) == -1)
		return (1);
	if (check_one_player(&p) == -1)
		return (1);
	if (!valid_map(&p))
		return (write(2, "Invalid map\n", 12), 1);
	p.mlx = mlx_init();
	if (!p.mlx)
		return (1);
	init_textures(&p);
	p.window = mlx_new_window(p.mlx, SW, SH, "First Map");
	if (!p.window)
		return (1);
	p.img = mlx_new_image(p.mlx, SW, SH);
	p.img_data = mlx_get_data_addr(p.img, &p.bpp, &p.line_length, &p.endian);
	clear_image(&p);
	cast_all_rays(&p);
	mlx_put_image_to_window(p.mlx, p.window, p.img, 0, 0);
	mlx_hook(p.window, 2, 0, (int (*)(int, void *))key_eshap, &p);
	mlx_hook(p.window, 17, 0, close_window, &p);
	mlx_loop(p.mlx);
	return (0);
}
