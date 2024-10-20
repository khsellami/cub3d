/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:33:45 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 13:36:20 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	count_words(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count += 1;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	ft_free_split(char **split_strings, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split_strings[i]);
		i++;
	}
	free(split_strings);
}

static int	word_len(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

static char	*strndup(char *s, int n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (dup != NULL)
		ft_strlcpy(dup, s, n + 1);
	return (dup);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		i;
	int		word_count;

	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		result[i] = strndup(s, word_len(s, c));
		if (!result[i])
		{
			ft_free_split(result, i);
			return (NULL);
		}
		s += word_len(s, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
