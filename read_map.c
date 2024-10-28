/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:29:04 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 11:26:45 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int ft_read_map(char *file, t_player *player)
{
	int		fd;
	char	*line;
	int		i;
	int		player_count;
	int		j;

	i = 0;
	player_count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, player) == -1)
			return (-1);
        else if (line[0] == '1' || line[0] == ' ')
            i++;
        free(line);
		line = get_next_line(fd);
	}
	if (!player->no || !player->so || !player->ea || !player->we)
        return (ft_putstr_fd("All textures must be provided (NO, SO, EA, WE)\n", 2), -1);
	player->map = malloc(sizeof(char *) * (i + 1));
	if (!player->map)
		return (close(fd), -1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	j = 0;
	line = get_next_line(fd);
	while (line && j < i)
	{
		if (line[0] == '1' || line[0] == ' ')
		{
			player->map[j] = malloc(strlen(line) + 1);
			if (!player->map[j])
			{
				for (int k = 0; k < j; k++)
					free(player->map[k]);
				free(player->map);
				close(fd);
				return -1;
			}
			strcpy(player->map[j], line);
			char *n_pos = strchr(player->map[j], 'N');
			char *s_pos = strchr(player->map[j], 'S');
			char *e_pos = strchr(player->map[j], 'E');
			char *w_pos = strchr(player->map[j], 'W');
			char *pos = n_pos ? n_pos : (s_pos ? s_pos : (e_pos ? e_pos : w_pos));
			if (pos)
			{
				int x_pos = pos - player->map[j];
				int y_pos = j;
				player->x = (x_pos * TILE_SIZE) + (TILE_SIZE / 2);
				player->y = (y_pos * TILE_SIZE) + (TILE_SIZE / 2);
				set_player_orientation(player, *pos);
				*pos = '0';
				player_count++;
			}
			j++;
		}
		free(line);
		line = get_next_line(fd);
	}
	player->map[j] = NULL;
	close(fd);
	if (player_count != 1)
		return (ft_putstr_fd("Found more than 1 player\n", 2), -1);
	return (1);
}
