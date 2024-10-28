/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:19:47 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/28 10:22:57 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	checkfilename(char *filename)
{
	int	len;
	int	fd;

	if (!filename)
		return (-1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub"))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}

int valid_map(t_player *p)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (p->map[i])
    {
       j = 0;
       while (p->map[i][j])
       {
            if (!valid_char_map(p->map[i][j]))
                return (0);
            if (p->map[i][j] == ' ' && !valid_space(p, i , j))
                return (0);
            if (p->map[i][j] == '0' && !entoure_mur(p , i,j))
                return (0);
            j++;
       }
       i++;
    }
    return (1);
}
