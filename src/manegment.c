/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manegment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:19:45 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:51:30 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	addone_manegment_controls(t_player *player, t_sdl *sdlka
, double frame)
{
	double	angv;
	double	tmp;

	angv = frame * SPEEDROOT;
	if (sdlka->event.key.keysym.sym == SDLK_e || sdlka->event.key.keysym.sym
	== SDLK_RIGHT)
	{
		tmp = player->dr.x;
		player->dr.x = player->dr.x * cos(-angv) - player->dr.y * sin(-angv);
		player->dr.y = tmp * sin(-angv) + player->dr.y * cos(-angv);
		tmp = player->pl.x;
		player->pl.x = player->pl.x * cos(-angv) - player->pl.y * sin(-angv);
		player->pl.y = tmp * sin(-angv) + player->pl.y * cos(-angv);
	}
	if (sdlka->event.key.keysym.sym == SDLK_q || sdlka->event.key.keysym.sym
	== SDLK_LEFT)
	{
		tmp = player->dr.x;
		player->dr.x = player->dr.x * cos(angv) - player->dr.y * sin(angv);
		player->dr.y = tmp * sin(angv) + player->dr.y * cos(angv);
		tmp = player->pl.x;
		player->pl.x = player->pl.x * cos(angv) - player->pl.y * sin(angv);
		player->pl.y = tmp * sin(angv) + player->pl.y * cos(angv);
	}
}

void			addone_maneg(t_player *player, t_sdl *sdlka
, double frame, t_world world)
{
	double	speed;

	speed = frame * SPEED;
	if (sdlka->event.key.keysym.sym == SDLK_s ||
	sdlka->event.key.keysym.sym == SDLK_DOWN)
	{
		if (world.world[(int)(player->ps.x - player->dr.x * speed + 0.1)]
		[(int)(player->ps.y)] == '0' &&
world.world[(int)(player->ps.x - player->dr.x * speed - 0.1)]
[(int)(player->ps.y)] == '0')
			player->ps.x -= player->dr.x * speed;
		if (world.world[(int)(player->ps.x)][(int)(player->ps.y
		- player->dr.y * speed + 0.1)] == '0' &&
			world.world[(int)(player->ps.x)][(int)(player->ps.y
			- player->dr.y * speed - 0.1)] == '0')
			player->ps.y -= player->dr.y * speed;
	}
}

void			manegment_controls(t_player *player, t_sdl *sdlka
, double frame, t_world world)
{
	double	speed;

	speed = frame * SPEED;
	if (sdlka->event.key.keysym.sym == SDLK_w || sdlka->event.key.keysym.sym
	== SDLK_UP)
	{
		if (world.world[(int)((player->ps.x + player->dr.x * speed) - 0.1)]
		[(int)(player->ps.y)] == '0'
		&& world.world[(int)((player->ps.x + player->dr.x * speed) + 0.1)]
		[(int)(player->ps.y)] == '0')
			player->ps.x += player->dr.x * speed;
		if (world.world[(int)(player->ps.x)][(int)(player->ps.y +
		player->dr.y * speed - 0.1)] == '0' &&
		world.world[(int)(player->ps.x)][(int)(player->ps.y +
		player->dr.y * speed + 0.1)] == '0')
			player->ps.y += player->dr.y * speed;
	}
	addone_maneg(player, sdlka, frame, world);
	addone_manegment_controls(player, sdlka, frame);
	sdlka->event.key.keysym.sym = 0;
}
