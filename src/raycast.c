/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:51:50 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 13:16:40 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	addon_ray(t_player *player, t_global_ray *raycast,
t_tmp *temper)
{
	if (raycast->ray_dir.x < 0)
	{
		temper->step.x = -1;
		temper->sidds.x = (player->ps.x - raycast->map_point.x)
		* temper->deldst.x;
	}
	else
	{
		temper->step.x = 1;
		temper->sidds.x = (raycast->map_point.x + 1.0 - player->ps.x)
		* temper->deldst.x;
	}
	if (raycast->ray_dir.y < 0)
	{
		temper->step.y = -1;
		temper->sidds.y = (player->ps.y - raycast->map_point.y)
		* temper->deldst.y;
	}
	else
	{
		temper->step.y = 1;
		temper->sidds.y = (raycast->map_point.y + 1.0 - player->ps.y)
		* temper->deldst.y;
	}
}

void			ray_func(t_player *player, t_global_ray *raycast,
t_tmp *temper, int x)
{
	double	cam;

	cam = 2 * x / (double)(WIDTH) - 1;
	raycast->ray_dir.x = player->dr.x + player->pl.x * cam;
	raycast->ray_dir.y = player->dr.y + player->pl.y * cam;
	raycast->map_point.x = (int)(player->ps.x);
	raycast->map_point.y = (int)(player->ps.y);
	temper->deldst.x = fabs(1 / raycast->ray_dir.x);
	temper->deldst.y = fabs(1 / raycast->ray_dir.y);
	addon_ray(player, raycast, temper);
}

static int		addone_hit(t_global_ray *raycast, t_tmp *temper, t_world world)
{
	int		hit;

	hit = 0;
	if (temper->sidds.x < temper->sidds.y)
	{
		temper->sidds.x += temper->deldst.x;
		raycast->map_point.x += temper->step.x;
		if (raycast->ray_dir.x > 0)
			raycast->side = 0;
		else
			raycast->side = 2;
	}
	else
	{
		temper->sidds.y += temper->deldst.y;
		raycast->map_point.y += temper->step.y;
		if (raycast->ray_dir.y > 0)
			raycast->side = 1;
		else
			raycast->side = 3;
	}
	if (world.world[raycast->map_point.x][raycast->map_point.y] != '0')
		hit = 1;
	return (hit);
}

void			algor_hit(t_player player, t_global_ray *raycast,
t_tmp *temper, t_world world)
{
	int		hit;

	hit = 0;
	while (hit == 0)
		hit = addone_hit(raycast, temper, world);
	if (raycast->side == 0 || raycast->side == 2)
		raycast->perwal = (raycast->map_point.x - player.ps.x +
		(1 - temper->step.x) / 2) / raycast->ray_dir.x;
	else
		raycast->perwal = (raycast->map_point.y - player.ps.y +
		(1 - temper->step.y) / 2) / raycast->ray_dir.y;
}

void			func_ray_logic(t_wolf_3d *wolf, t_pic *pic,
t_player player, t_world world)
{
	t_fc_n	f;
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_func(&player, &f.raycast, &f.temper, x);
		algor_hit(player, &f.raycast, &f.temper, world);
		find_wall(player, &f.raycast, &f.temper);
		set_pixel_wall(wolf, &f, pic, x);
		find_wall_cell(f.raycast, &f.floorwall);
		f.x = x;
		set_pixel_floor_cell(wolf, pic, player, &f);
	}
}
