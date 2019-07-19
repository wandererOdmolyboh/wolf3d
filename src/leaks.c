/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:50:50 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/27 16:30:32 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	sdl_leaks(t_wolf_3d *wolf)
{
	SDL_DestroyTexture(wolf->sdlka.textur);
	SDL_DestroyRenderer(wolf->sdlka.ren);
	SDL_DestroyWindow(wolf->sdlka.win);
}

void	leaks_free(t_wolf_3d *wolf, int *pix)
{
	int	i;

	i = -1;
	while (++i < TEXT_NUM)
		free(wolf->texture[i]);
	if (pix)
		free(pix);
}

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	split = NULL;
}
