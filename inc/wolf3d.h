/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 09:27:12 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/06/30 14:57:48 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
**			LIBS
*/
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include "SDL2_image/SDL_image.h"
# include "SDL2/SDL.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>

/*
**			MAGIC_NUMBERS
*/

# define WIDTH 1266
# define HEIGHT 768
# define TRUE 1
# define FALSE 0
# define TEXT_W 64
# define TEXT_H 64
# define BUFF_SIZE 80
# define TEXT_NUM 18
# define DEAFULT_STATE 0
# define BONUS 6
# define BONUSM 12
# define SPEED 4
# define SPEEDROOT 2

/*
**			TYPEDEF
*/

typedef struct s_point_i		t_point_i;
typedef struct s_point_d		t_point_d;
typedef struct s_normi			t_norm;
typedef struct s_wolf_3d		t_wolf_3d;
typedef struct s_sdl			t_sdl;
typedef struct s_player			t_player;
typedef struct s_pic			t_pic;
typedef struct s_world			t_world;
typedef struct s_frame			t_frame;
typedef struct s_global_ray		t_global_ray;
typedef struct s_tmp			t_tmp;
typedef struct s_fck_norm		t_fc_n;

/*
**			STRUCT
*/

struct							s_point_i
{
	int							x;
	int							y;
};

struct							s_point_d
{
	double						x;
	double						y;
};

struct							s_world
{
	char						**world;
};

struct							s_pic
{
	int							w;
	int							h;
	int							*pixels;
};

struct							s_sdl
{
	SDL_Window					*win;
	SDL_Renderer				*ren;
	SDL_Texture					*textur;
	SDL_Event					event;
};

struct							s_player
{
	t_point_d					ps;
	t_point_d					dr;
	t_point_d					pl;
	int							speed;
};

struct							s_frame
{
	double						timer;
	double						otime;
	double						frmtime;
};

struct							s_global_ray
{
	t_point_d					ray_dir;
	t_point_i					map_point;
	double						perwal;
	int							drawst;
	int							drawnd;
	double						wall;
	int							side;
	int							color;
};

struct							s_tmp
{
	t_point_i					step;
	t_point_d					deldst;
	t_point_d					sidds;
	t_point_i					tex;
	int							lheit;
};

struct							s_wolf_3d
{
	int							textn;
	int							*texture[TEXT_NUM];
	t_sdl						sdlka;
	t_player					player;
	t_pic						pic;
	t_world						world;
};

struct							s_normi
{
	int							color;
	double						diswal;
	double						dplr;
	double						curdist;
	double						weight;
	t_point_d					currfl;
	t_point_i					flrtex;
};

struct							s_fck_norm
{
	t_global_ray				raycast;
	t_tmp						temper;
	t_point_d					floorwall;
	int							x;
};

/*
**			FUNC
*/

int								check_map(char *world_map);
int								initial_sdl(t_wolf_3d *wolf, t_pic *pic);
int								create_tex_wolf(t_wolf_3d *wolf);
int								validator(char **map);
char							*func_read(int fd);
void							sdl_leaks(t_wolf_3d *wolf);
void							leaks_free(t_wolf_3d *wolf, int *pix);
void							initial_value(t_wolf_3d *wolf,
t_frame *frame, t_world world);
void							free_split(char **split);
void							set_pixel_wall(t_wolf_3d *wolf, t_fc_n *f,
t_pic *pic, int x);
void							set_pixel_floor_cell(t_wolf_3d *wolf,
t_pic *pic, t_player player, t_fc_n *f);
void							manegment_controls(t_player *player, t_sdl
*sdlka, double frametime, t_world world);
void							func_ray_logic(t_wolf_3d *wolf, t_pic *pic,
t_player player,
t_world world);
void							find_wall(t_player player, t_global_ray
*raycast, t_tmp *temper);
void							find_wall_cell(t_global_ray raycast,
t_point_d *floorwall);

#endif
