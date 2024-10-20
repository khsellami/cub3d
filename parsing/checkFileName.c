/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkFileName.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:20:33 by ksellami          #+#    #+#             */
/*   Updated: 2024/10/20 11:21:00 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int valid_file_name(char *f)
{
    int fd;

    if (!f || ft_strlen(f) < 4 || ft_strcmp(&f[ft_strlen(f) - 4], ".cub"))
        return (0);
    fd = open(f, O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return (1);
}
