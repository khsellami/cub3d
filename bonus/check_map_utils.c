/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:25:24 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/29 13:20:29 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int valid_char_map(char c)
{
    if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c!= '\n')
        return (0);
    return (1);
}

int not_mur_or_space(char c)
{
    if (c != ' ' && c != '1' && c != '\n' && c != '\0')
        return (1);
    return (0);
}

int valid_space(t_player *p, int i, int j)
{
    if (p->map && p->map[i + 1] && not_mur_or_space(p->map[i + 1][j]))
        return (0);
    if (p->map && i -1 >= 0 && not_mur_or_space(p->map[i - 1][j]))
        return (0);
    if (p->map && p->map[i][j + 1] && not_mur_or_space(p->map[i][j + 1]))
        return (0);
    if (p->map && j - 1 >= 0 && not_mur_or_space(p->map[i][j -1]))
        return (0);
    return (1);
}

int entoure_mur(t_player *p, int i, int j)
{
	if (p->map && !p->map[i + 1])
		return (0);
	if (p->map && i - 1 < 0)
		return (0);
	if (p->map && !p->map[i][j + 1])
		return (0);
	if (p->map && j - 1 < 0)
		return (0);
	return (1);
}
