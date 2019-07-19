/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_w_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:57:24 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:00:01 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	find_wall(t_player player, t_global_ray *raycast, t_tmp *temper)
{
	temper->lheit = (int)(HEIGHT / raycast->perwal);
	raycast->drawst = -temper->lheit / 2 + HEIGHT / 2;
	if (raycast->drawst < 0)
		raycast->drawst = 0;
	raycast->drawnd = temper->lheit / 2 + HEIGHT / 2;
	if (raycast->drawnd >= HEIGHT)
		raycast->drawnd = HEIGHT - 1;
	if (raycast->side == 0 || raycast->side == 2)
		raycast->wall = player.ps.y + raycast->perwal * raycast->ray_dir.y;
	else
		raycast->wall = player.ps.x + raycast->perwal * raycast->ray_dir.x;
	raycast->wall -= floor((raycast->wall));
	temper->tex.x = (int)(raycast->wall * (double)(TEXT_W));
	if ((raycast->side == 0 || raycast->side == 2) && raycast->ray_dir.x > 0)
		temper->tex.x = TEXT_W - temper->tex.x - 1;
	if ((raycast->side == 1 || raycast->side == 3) && raycast->ray_dir.y < 0)
		temper->tex.x = TEXT_W - temper->tex.x - 1;
}

void	find_wall_cell(t_global_ray raycast, t_point_d *floorwall)
{
	if ((raycast.side == 0 || raycast.side == 2) && raycast.ray_dir.x > 0)
	{
		floorwall->x = raycast.map_point.x;
		floorwall->y = raycast.map_point.y + raycast.wall;
	}
	else if ((raycast.side == 0 || raycast.side == 2) && raycast.ray_dir.x < 0)
	{
		floorwall->x = raycast.map_point.x + 1.0;
		floorwall->y = raycast.map_point.y + raycast.wall;
	}
	else if ((raycast.side == 1 || raycast.side == 2) && raycast.ray_dir.y > 0)
	{
		floorwall->x = raycast.map_point.x + raycast.wall;
		floorwall->y = raycast.map_point.y;
	}
	else
	{
		floorwall->x = raycast.map_point.x + raycast.wall;
		floorwall->y = raycast.map_point.y + 1.0;
	}
}
