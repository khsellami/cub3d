/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:49 by kahmada           #+#    #+#             */
/*   Updated: 2024/11/03 17:29:52 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < dstsize)
		ft_memcpy(dst, src, src_len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (src_len);
}

static void	free_sp(char **str, int count)
{
	int	i;

	i = 0;
	while (str[i] && i < count)
		free(str[i++]);
	free(str);
}

static	int	count_word(char  *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static	char	**fill_sp(char **res, char *s, char c)
{
	int	i;
	int	temp;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			temp = i;
			while (s[i] != c && s[i])
				i++;
			res[j] = malloc(i - temp + 1);
			if (!res[j])
				return (NULL);
			ft_strlcpy(res[j++], s + temp, i - temp + 1);
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_sp(result, s, c))
	{
		free_sp(result, count);
		return (NULL);
	}
	return (result);
}
