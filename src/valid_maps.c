/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:48:30 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 13:48:33 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int	nor_valid(char **map, int leny, int lenx, int ch)
{
	int	k;

	k = -1;
	while (map[leny][++k])
	{
		if (map[leny][k] == '0')
			ch = -1;
	}
	k = -1;
	while (map[++k])
	{
		if (map[k][0] == '0')
			ch = -1;
	}
	k = -1;
	while (map[++k])
	{
		if (map[k][lenx] == '0')
			ch = -1;
	}
	return (ch);
}

static	int	validat(char **map)
{
	int	k;
	int	ch;
	int	lenx;
	int	leny;

	leny = -1;
	while (map[++leny])
		;
	leny--;
	lenx = ft_strlen(map[0]);
	lenx--;
	ch = 0;
	k = -1;
	while (map[0][++k])
	{
		if (map[0][k] == '0')
			ch = -1;
	}
	return (nor_valid(map, leny, lenx, ch));
}

static	int	validate(char **map)
{
	int i;
	int k;
	int ch;

	ch = -1;
	i = -1;
	while (map[++i])
	{
		k = -1;
		while (map[i][++k])
		{
			if (map[i][k] == '0')
				ch = 0;
		}
	}
	if (ch == -1)
		return (ch);
	if (-1 == validat(map))
		return (-1);
	return (0);
}

int			validator(char **map)
{
	int	i;
	int	k;
	int	tmp;
	int	dop;

	dop = 0;
	i = -1;
	while (map[++i])
		;
	if (i == 0 || i == 1 || i == 2)
		return (-1);
	tmp = i;
	i = -1;
	dop = ft_strlen(map[0]);
	while (++i != tmp)
	{
		k = -1;
		while (map[i][++k])
			;
		if (k == 0 || k == 1 || k == 2)
			return (-1);
		if (k != dop)
			return (-1);
	}
	return (validate(map));
}
