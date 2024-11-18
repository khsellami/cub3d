/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:06:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/18 11:44:22 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_atoi(char *str)
{
	int						i;
	int						ne;
	unsigned long long int	num;

	i = 0;
	ne = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ne *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (ne == 1 && num > LONG_MAX / 10)
			return (-1);
		else if (ne == -1 && num > LONG_MAX / 10)
			return (0);
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * ne);
}
