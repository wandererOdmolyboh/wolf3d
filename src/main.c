/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:26:24 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:59:14 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		framer(t_frame *frame)
{
	frame->otime = frame->timer;
	frame->timer = SDL_GetTicks();
	frame->frmtime = (frame->timer - frame->otime) / 1000.0;
}

void		game(t_world world, t_wolf_3d *wolf, t_pic *pic, t_frame *frame)
{
	func_ray_logic(wolf, pic, wolf->player, world);
	SDL_UpdateTexture(wolf->sdlka.textur, NULL, pic->pixels, WIDTH * 4);
	SDL_RenderCopy(wolf->sdlka.ren, wolf->sdlka.textur, NULL, NULL);
	SDL_RenderPresent(wolf->sdlka.ren);
	framer(frame);
	if (wolf->sdlka.event.type == SDL_KEYDOWN)
		manegment_controls(&wolf->player, &wolf->sdlka,
		frame->frmtime, world);
	if (wolf->sdlka.event.key.keysym.sym == SDLK_1)
		wolf->textn = DEAFULT_STATE;
	if (wolf->sdlka.event.key.keysym.sym == SDLK_2)
		wolf->textn = BONUS;
	if (wolf->sdlka.event.key.keysym.sym == SDLK_3)
		wolf->textn = BONUSM;
}

int			rung_game(t_world world)
{
	t_wolf_3d			wolf;
	t_pic				pic;
	t_frame				frame;

	wolf.textn = 0;
	initial_value(&wolf, &frame, world);
	if (initial_sdl(&wolf, &pic) == -1 || create_tex_wolf(&wolf) == -1)
	{
		leaks_free(&wolf, pic.pixels);
		sdl_leaks(&wolf);
		return (-1);
	}
	while (TRUE)
	{
		game(world, &wolf, &pic, &frame);
		if (SDL_PollEvent(&wolf.sdlka.event) && (wolf.sdlka.event.type
		== SDL_QUIT || wolf.sdlka.event.key.keysym.sym == SDLK_ESCAPE))
			break ;
	}
	leaks_free(&wolf, pic.pixels);
	sdl_leaks(&wolf);
	return (0);
}

static	int	check_path(char *s)
{
	ft_putstr(s);
	ft_putendl(" is run");
	if (ft_strcmp(s, "./wolf3d") != 0)
	{
		write(1, "Invalid executable path\n", 24);
		return (-1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	char	*world;
	char	**world_map;
	t_world	world2;

	if (WIDTH < 300 || HEIGHT < 300 || WIDTH > 1600 || HEIGHT > 1300)
		return (-1);
	if (argc == 2 && check_path(*argv) != -1)
	{
		argc = open(argv[1], O_RDONLY);
		if (((world = func_read(argc)) != NULL) && check_map(world) == 0)
		{
			world_map = ft_strsplit(world, '\n');
			if (world_map)
			{
				world2.world = world_map;
				if (validator(world2.world) == 0)
					rung_game(world2);
				free_split(world_map);
			}
		}
		close(argc);
		free(world);
	}
	return (0);
}
