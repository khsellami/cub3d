/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:01:04 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/21 17:54:48 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	mouse_motion(int x, int y, t_player *player)
{
	static int	old_x;

	if (0 <= x && x <= SW && 0 <= y && y <= SH)
	{
		if (x > old_x)
			player->rotationangle += 0.3;
		else if (x < old_x)
			player->rotationangle -= 0.3;
		old_x = x;
	}
	return (0);
}
