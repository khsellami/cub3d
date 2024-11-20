/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:21:20 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/20 17:21:48 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	space_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (!(*line) || *line == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}
