/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:07:14 by ksellami          #+#    #+#             */
/*   Updated: 2024/11/03 17:28:57 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static char	*ft_read(int fd, char *str)
{
	int		byteread;
	char	*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byteread = 1;
	while (byteread)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == 0)
			break ;
		if (byteread == -1)
			return (free(str), str = NULL, free(buffer), buffer = NULL, NULL);
		buffer[byteread] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n') != NULL)
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (str);
}

static char	*getthisline(char *t)
{
	char	*line;
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (!t)
		return (NULL);
	while (t[n] && t[n] != '\n')
		n++;
	if (t[n] == '\n')
		n++;
	line = malloc(n + 1);
	if (!line)
		return (NULL);
	while (i < n)
	{
		line[i] = t[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*rest(char *tmp)
{
	char	*newline_pos;
	char	*rst;

	newline_pos = ft_strchr(tmp, '\n');
	if (!newline_pos)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	newline_pos++;
	rst = ft_strdup(newline_pos);
	if (!rst)
		return (NULL);
	free(tmp);
	tmp = NULL;
	return (rst);
}

char	*get_next_line(int fd)
{
	char		*ln;
	static char	*str;

	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| fd < 0 || fd > INT_MAX)
	{
		if (str != NULL)
			return (free(str), str = NULL, NULL);
		return (NULL);
	}
	str = ft_read(fd, str);
	if (!str || !*str)
		return (free(str), str = NULL, NULL);
	ln = getthisline(str);
	if (!ln)
		return (free(str), str = NULL, NULL);
	str = rest(str);
	return (ln);
}
