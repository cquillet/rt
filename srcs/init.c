/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:12:09 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:19:19 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Init the base struct
*/

static t_px	**init_tab_px(int winy, int winx)
{
	t_px	**t;
	int		i;

	if ((t = (t_px**)malloc(sizeof(t_px*) * winy)))
	{
		i = -1;
		while (++i < winy)
			t[i] = (t_px*)malloc(sizeof(t_px) * winx);
	}
	return (t);
}

void		init_b(t_b *b)
{
	b->p = 1.0;
	b->win = NULL;
	b->winx = 640;
	b->winy = 480;
	init_vp(b);
	init_cam(b);
	b->lux = NULL;
	b->obj = NULL;
	b->act = NULL;
	b->amb = init_col(0.0, 0.0, 0.0);
	b->max = 1000.0;
	b->aliasing = 1;
	b->colmax = 0.0;
	b->gamma = 1.0;
	b->saturation = 7.0;
	b->draw_lights = 1;
	b->depth = 1;
	b->max_dist = 10000.0;
	b->nb_lux = 0;
	b->nb_obj = 0;
	b->inter = init_inter();
	b->tab_px = init_tab_px(b->winy, b->winx);
}

/*
** SDL windows init
*/

void		init_win(t_b *b)
{
	if (!(b->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											b->winx,
											b->winy,
											SDL_WINDOW_SHOWN)))
		error_quit(b, 1);
	b->img = SDL_GetWindowSurface(b->win);
}

/*
** Init the cam strcut values
*/

void		init_cam(t_b *b)
{
	b->cam.pos = init_vect(0, 0, -b->vp.dist);
	b->cam.dir = init_vect(0, 0, 1);
	refresh_dirright(&b->cam, init_vect(0, 1, 0));
}

/*
** Init the lux struct
*/

t_lux		init_lux(t_v pos, t_col dif, t_col spe)
{
	t_lux	lux;

	lux.ori = pos;
	lux.dif = dif;
	lux.spe = spe;
	lux.atn = 1.0;
	lux.amp_cst = 1.0;
	lux.amp_lin = 0.000;
	lux.amp_quad = 0.0;
	lux.next = NULL;
	return (lux);
}
