/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:06:44 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/09 19:36:40 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	*ft_memset(void *s, int c, int n)
{
	unsigned char	*str;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	while (n > 0)
	{
		*(str++) = (unsigned char)c;
		n--;
	}
	return (s);
}

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
