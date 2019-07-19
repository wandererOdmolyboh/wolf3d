/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intitial_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:50:58 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:59:36 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_pic	create_image(int width, int height)
{
	t_pic	pic;

	pic.w = width;
	pic.h = height;
	if ((pic.pixels = ft_memalloc(sizeof(int) * (pic.w *
	pic.h))) == NULL)
		write(1, "Memory allocation fault\n", 25);
	return (pic);
}

static int		dop_initial(t_wolf_3d *wolf)
{
	wolf->sdlka.ren = SDL_CreateRenderer(wolf->sdlka.win, -1,
	SDL_RENDERER_ACCELERATED
	| SDL_RENDERER_PRESENTVSYNC);
	if (wolf->sdlka.ren == NULL)
	{
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (-1);
	}
	if ((wolf->sdlka.textur = SDL_CreateTexture(wolf->sdlka.ren,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	WIDTH, HEIGHT)) == NULL)
		return (-1);
	return (0);
}

int				initial_sdl(t_wolf_3d *wolf, t_pic *pic)
{
	*pic = create_image(WIDTH, HEIGHT);
	if ((pic->pixels) == NULL)
		return (-1);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return (-1);
	}
	wolf->sdlka.win = SDL_CreateWindow("Wolf3d", 100, 100, WIDTH, HEIGHT,
	SDL_WINDOW_SHOWN);
	if (wolf->sdlka.win == NULL)
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return (-1);
	}
	return (dop_initial(wolf));
}

void			initial_value(t_wolf_3d *wolf, t_frame *frame, t_world world)
{
	int i;
	int k;

	i = -1;
	while (world.world[++i])
	{
		k = -1;
		while (world.world[i][++k])
		{
			if (world.world[i][k] == '0')
				break ;
		}
		if (world.world[i][k] == '0')
			break ;
	}
	wolf->player.ps.x = i + 0.2;
	wolf->player.ps.y = k + 0.2;
	wolf->player.dr.x = -1.0;
	wolf->player.dr.y = 0.0;
	wolf->player.pl.x = 0.0;
	wolf->player.pl.y = 0.66;
	frame->timer = 0;
	frame->otime = 0;
}
