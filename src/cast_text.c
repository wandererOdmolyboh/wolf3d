/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:51:53 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 13:07:03 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ret_color(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r << (16)) | (g << (8)) | b);
}

static int	get_color_pix(void *ptr, int i)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)ptr;
	return (ret_color(tmp[i + 2], tmp[i + 1], tmp[i]));
}

static int	cast_image_to_pix(int *pixels, const char *path)
{
	int			i;
	int			size;
	int			alph_ch;
	SDL_Surface	*surf;

	i = 0;
	size = (int)(TEXT_H * TEXT_W);
	alph_ch = 0;
	if ((surf = IMG_Load(path)) == NULL)
	{
		SDL_Log("SDL: %s", SDL_GetError());
		return (-1);
	}
	while (i < size)
	{
		pixels[i++] = get_color_pix(surf->pixels, alph_ch);
		alph_ch += (4);
	}
	SDL_FreeSurface(surf);
	return (0);
}

static	int	fill_texture(t_wolf_3d *wolf)
{
	int			i;
	char		*leaks;
	char		*s;

	leaks = NULL;
	i = -1;
	while (++i < TEXT_NUM)
	{
		s = ft_itoa(i);
		leaks = ft_strjoin("./pic/", s);
		if (s)
			free(s);
		s = ft_strjoin(leaks, ".png");
		if (leaks)
			free(leaks);
		if ((cast_image_to_pix(wolf->texture[i], s)) == -1)
		{
			if (s)
				free(s);
			return (-1);
		}
		if (s)
			free(s);
	}
	return (0);
}

int			create_tex_wolf(t_wolf_3d *wolf)
{
	int			i;

	i = -1;
	while (++i < TEXT_NUM)
		wolf->texture[i] = (int *)malloc(sizeof(int) *
		(int)TEXT_H * (int)TEXT_W);
	if (fill_texture(wolf) == -1)
		return (-1);
	return (0);
}
