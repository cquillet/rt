/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:55:30 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/22 20:08:17 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Event for objects
**
** 0 = Lumiere
** 1 = Sphere
** 2 = Plan
** 3 = Cylindre
** 4 = Cone
*/

void	event_obj(t_b *b, int ev)
{
	t_px	px;
	t_v		pos;
	t_v		axis;

	SDL_GetMouseState(&px.x, &px.y);
	pos = init_vect(b->cam.pos.x, b->cam.pos.y, b->cam.pos.z + 7.0);
	axis = init_vect(0.0, 1.0, 0.0);
	if (ev == SDLK_i || ev == SDLK_j || ev == SDLK_k || ev == SDLK_l
		|| ev == SDLK_u || ev == SDLK_o)
		ev_move_obj(b, ev);
	else if (ev == SDLK_DELETE)
		delete_obj(b, b->id);
	else if (ev == SDLK_KP_0)
		add_lux(b, init_lux(pos, init_col(0.7, 0.7, 0.7),
													init_col(0.3, 0.3, 0.3)));
	else if (ev == SDLK_KP_1)
		add_obj(b, init_sph(pos, init_col(COL_WHITE), 1.0));
	else if (ev == SDLK_KP_2)
		add_obj(b, init_plane(pos, 5.0, init_col(COL_WHITE)));
	else if (ev == SDLK_KP_3)
		add_obj(b, init_cyl(pos, init_col(COL_WHITE), axis, 2.));
	else if (ev == SDLK_KP_4)
		add_obj(b, init_cone(pos, init_col(COL_WHITE), axis, 20.));
}

/*
** Moving for obj keys : up = i | down = k | right = l | left = j
**							forward = u | backward = o
*/

void	ev_move_obj(t_b *b, int ev)
{
	t_obj	*obj;

	if (!(obj = search_obj(b, b->id)))
		return (ev_move_lum(b, ev));
	if (ev == SDLK_i)
		obj->ori.x += 0.551;
	else if (ev == SDLK_k)
		obj->ori.x -= 0.551;
	else if (ev == SDLK_l)
		obj->ori.y += 0.552;
	else if (ev == SDLK_j)
		obj->ori.y -= 0.552;
	else if (ev == SDLK_u)
		obj->ori.z -= 2.003;
	else if (ev == SDLK_o)
		obj->ori.z += 2.003;
}

/*
** Moving for lux keys : up = i | down = k | right = l | left = j
**							forward = u | backward = o
*/

void	ev_move_lum(t_b *b, int ev)
{
	t_lux	*lux;

	if (!(lux = search_lux(b, b->id)))
		return ;
	if (ev == SDLK_i)
		lux->ori.x += 0.111;
	else if (ev == SDLK_k)
		lux->ori.x -= 0.111;
	else if (ev == SDLK_l)
		lux->ori.y += 0.112;
	else if (ev == SDLK_j)
		lux->ori.y -= 0.112;
	else if (ev == SDLK_u)
		lux->ori.z -= 2.013;
	else if (ev == SDLK_o)
		lux->ori.z += 2.013;
}

void	ev_mouse(t_b *b)
{
	t_px px;

	SDL_GetMouseState(&px.x, &px.y);
	b->id = b->tab_px[px.y][px.x].id;
}
