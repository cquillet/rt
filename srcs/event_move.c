/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:24:01 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 15:24:22 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		event_move(t_b *b, int ev)
{
	if (ev == SDLK_w || ev == SDLK_a || ev == SDLK_s || ev == SDLK_d ||
			ev == SDLK_KP_MINUS || ev == SDLK_KP_PLUS)
		ev_move_cam(b, ev);
	else if (ev == SDLK_i || ev == SDLK_j || ev == SDLK_k || ev == SDLK_l
		|| ev == SDLK_u || ev == SDLK_o || ev == SDLK_DELETE || ev == SDLK_KP_0
		|| ev == SDLK_KP_1 || ev == SDLK_KP_2 || ev == SDLK_KP_3
		|| ev == SDLK_KP_4 || ev == SDLK_KP_5)
		event_obj(b, ev);
	return (1);
}

/*
** Event for rotating the vector
*/

void	ev_rotate_xy(t_b *b, int ev)
{
	double	angle;

	angle = 3.0 * M_PI / 180.0;
	if (ev == SDLK_DOWN)
	{
		b->cam.dir = vect_rotate(b->cam.dir, -angle, b->cam.dirright);
		b->cam.dirup = vect_rotate(b->cam.dirup, -angle, b->cam.dirright);
	}
	else if (ev == SDLK_UP)
	{
		b->cam.dir = vect_rotate(b->cam.dir, angle, b->cam.dirright);
		b->cam.dirup = vect_rotate(b->cam.dirup, angle, b->cam.dirright);
	}
	else if (ev == SDLK_RIGHT)
	{
		b->cam.dir = vect_rotate(b->cam.dir, angle, b->cam.dirup);
		b->cam.dirright = vect_rotate(b->cam.dirup, angle, b->cam.dirup);
	}
	else if (ev == SDLK_LEFT)
	{
		b->cam.dir = vect_rotate(b->cam.dir, -angle, b->cam.dirup);
		b->cam.dirright = vect_rotate(b->cam.dirup, -angle, b->cam.dirup);
	}
}

/*
** Moving keys : up | down | right | left
*/

void	ev_move_cam(t_b *b, int ev)
{
	if (ev == SDLK_w)
		b->cam.pos = vect_add(b->cam.pos, vect_multnb(&b->cam.dirup, 0.5));
	else if (ev == SDLK_s)
		b->cam.pos = vect_sub(b->cam.pos, vect_multnb(&b->cam.dirup, 0.5));
	else if (ev == SDLK_a)
		b->cam.pos = vect_sub(b->cam.pos, vect_multnb(&b->cam.dirright, 0.5));
	else if (ev == SDLK_d)
		b->cam.pos = vect_add(b->cam.pos, vect_multnb(&b->cam.dirright, 0.5));
	else if (ev == SDLK_KP_PLUS)
		b->cam.pos = vect_add(b->cam.pos, vect_multnb(&b->cam.dir, 3));
	else if (ev == SDLK_KP_MINUS)
		b->cam.pos = vect_sub(b->cam.pos, vect_multnb(&b->cam.dir, 3));
}
