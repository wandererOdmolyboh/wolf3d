/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:45:57 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 13:57:44 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*func_read(int fd)
{
	char	*world_map;
	int		len;
	char	*buf;
	char	*leaks;

	world_map = NULL;
	if ((buf = (char *)malloc(BUFF_SIZE + 1)) == NULL ||
	fd < 0 || BUFF_SIZE < 1 || read(fd, NULL, 0) < 0)
	{
		free(buf);
		write(1, "Sometnhing wrong in read\n", 25);
		return (NULL);
	}
	while ((len = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[len] = '\0';
		leaks = world_map;
		world_map = ft_strjoin(world_map, buf);
		free(leaks);
	}
	free(buf);
	return (world_map);
}
