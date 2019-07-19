/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_w_pixels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:51:59 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:01:55 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_pixel(t_pic *pic, int x, int y, int color)
{
	if (x < 0 || x > (int)pic->w || y < 0 || y > (int)pic->h)
		return ;
	pic->pixels[x + y * pic->w] = color;
}

void	set_pixel_wall(t_wolf_3d *wolf, t_fc_n *f, t_pic *pic, int x)
{
	int		y;
	int		tmp;

	y = f->raycast.drawst - 1;
	while (++y < f->raycast.drawnd)
	{
		tmp = y * 256 - HEIGHT * 128 + f->temper.lheit * 128;
		f->temper.tex.y = ((tmp * TEXT_H) / f->temper.lheit) / 256;
		f->raycast.color = wolf->texture[wolf->textn + 2]
		[TEXT_W * f->temper.tex.y + f->temper.tex.x];
		if (f->raycast.side == 1)
			f->raycast.color = wolf->texture[wolf->textn + 3]
			[TEXT_W * f->temper.tex.y + f->temper.tex.x];
		if (f->raycast.side == 2)
			f->raycast.color = wolf->texture[wolf->textn + 4][TEXT_W *
			f->temper.tex.y + f->temper.tex.x];
		if (f->raycast.side == 3)
			f->raycast.color = wolf->texture[wolf->textn + 5][TEXT_W *
			f->temper.tex.y + f->temper.tex.x];
		set_pixel(pic, x, y, f->raycast.color);
	}
}

void	set_pixel_floor_cell(t_wolf_3d *wolf, t_pic *pic, t_player player,
t_fc_n *f)
{
	t_norm	nor;
	int		y;

	nor.diswal = f->raycast.perwal;
	nor.dplr = 0.0;
	if (f->raycast.drawnd < 0)
		f->raycast.drawnd = HEIGHT;
	y = f->raycast.drawnd;
	while (++y < HEIGHT)
	{
		nor.curdist = HEIGHT / (2.0 * y - HEIGHT);
		nor.weight = (nor.curdist - nor.dplr) / (nor.diswal - nor.dplr);
		nor.currfl.x = nor.weight * f->floorwall.x + (1.0 - nor.weight)
		* player.ps.x;
		nor.currfl.y = nor.weight * f->floorwall.y + (1.0 - nor.weight)
		* player.ps.y;
		nor.flrtex.x = (int)(nor.currfl.x * TEXT_W) % TEXT_W;
		nor.flrtex.y = (int)(nor.currfl.y * TEXT_H) % TEXT_H;
		nor.color = wolf->texture[wolf->textn + 1][TEXT_W * nor.flrtex.y +
		nor.flrtex.x];
		set_pixel(pic, f->x, y, nor.color);
		nor.color = wolf->texture[wolf->textn][TEXT_W * nor.flrtex.y
		+ nor.flrtex.x];
		set_pixel(pic, f->x, HEIGHT - y, nor.color);
	}
}
