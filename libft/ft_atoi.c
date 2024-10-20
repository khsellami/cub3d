/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:34:01 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:35:18 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_atoi(char *str)
{
	int					i;
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
