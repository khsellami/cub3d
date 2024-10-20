/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:42:19 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:44:50 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*k;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = (char *) malloc (i + j + 1);
	if (!k)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		k[j++] = s1[i++];
	i = 0;
	while (s2[i])
		k[j++] = s2[i++];
	k[j] = '\0';
	free(s1);
	s1 = NULL;
	return (k);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlcpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
