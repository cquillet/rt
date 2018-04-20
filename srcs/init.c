/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:12:09 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/03 20:31:01 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Init the base struct
*/

void	init_b(t_b *b)
{
	int	i;

	b->p = 1.0;
	b->win = NULL;
	b->winx = 640 * 1.5;
	b->winy = 480 * 1.5;
	init_vp(b);
	init_cam(b);
	b->vl = NULL;
	b->lux = NULL;
	b->obj = NULL;
	b->amb = init_col(0.0, 0.0, 0.0);
	b->max = 1000;
	b->aliasing = 2;
	b->colmax = 0.0;
	b->gamma = 1.0;
	b->saturation = 7.0;
	b->rec = 0;
	b->draw_lights = 1;
	b->tab_px = (t_px**)malloc(sizeof(t_px*) * b->winy);
	i = -1;
	while (++i < b->winy)
		b->tab_px[i] = (t_px*)malloc(sizeof(t_px) * b->winx);
}

/*
** SDL windows init
*/

void	init_win(t_b *b)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		error_quit(1);
	if (!(b->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											b->winx,
											b->winy,
											SDL_WINDOW_SHOWN)))
		error_quit(1);
	b->img = SDL_GetWindowSurface(b->win);
}

/*
** Init the cam strcut values
*/

void	init_cam(t_b *b)
{
	b->cam.pos = init_vect(0, 0, -b->vp.dist);
	b->cam.dir = init_vect(0, 0, 1);
	refresh_dirright(&b->cam, init_vect(0, 1, 0));
}

/*
** Init the lux struct
*/

t_lux	init_lux(t_v pos, t_col dif, t_col spe)
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
