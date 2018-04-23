/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sheit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:38:45 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/23 15:43:15 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_b		copy_base(t_b *b, t_b *bl)
{
	bl->max = b->max;
	bl->colmax = b->colmax;
	bl->gamma = b->gamma;
	bl->id = b->id;
	bl->p = b->p;
	bl->winx = b->winx;
	bl->winy = b->winy;
	bl->maxid = b->maxid;
	bl->aliasing = b->aliasing;
	bl->act = b->act;
	bl->tab_px = b->tab_px;
	bl->vl = b->vl;
	bl->cam = b->cam;
	bl->vp = b->vp;
	bl->obj = b->obj;
	bl->lux = b->lux;
	bl->amb = b->amb;
	bl->inter = b->inter;
	bl->win = b->win;
	bl->img = b->img;
	return (*bl);
}

/*
** Init an intersection struct
*/

t_inter	init_inter(void)
{
	t_inter	inter;

	inter.dist = 0.;
	inter.id = -1;
	inter.n = init_vect(0., 0., 0.);
	inter.tex = init_tex();
	return (inter);
}

/*
** Init for the viewplane struct
*/

void	init_vp(t_b *b)
{
	b->vp.w = 0.5;
	b->vp.h = 0.35;
	b->vp.xi = b->vp.w / (double)b->winx;
	b->vp.yi = b->vp.h / (double)b->winy;
	b->vp.dist = 1.0;
	b->vp.upleft = vect_add(b->cam.pos, dir_vp_upleft(b));
}

/*
** init texture struct
*/

t_tex	init_tex(void)
{
	t_tex	tex;

	tex.rug = 1.0;
	tex.plasti = 0.0;
	tex.refra = 0.0;
	tex.trans = 0.0;
	tex.hidden = 0;
	tex.reflect = 0.0;
	tex.col = init_col(1.0, 1.0, 1.0);
	tex.ka = init_col(0.5, 0.5, 0.5);
	tex.kd = init_col(1.0, 1.0, 1.0);
	tex.ks = init_col(0.0, 0.0, 0.0);
	return (tex);
}

/*
** Init the action struct
** Action : 1 = Ellipse | 2 = axe	| 3 = color
** Axis   : 1 = X 		| 2 = Y 	| 3 = Z
*/

t_act	init_act(t_obj *obj1, int action, int axis)
{
	t_act	act;

	act.action = action;
	act.obj1 = obj1;
	act.speed = 0.5;
	act.p = 0;
	act.next = NULL;
	act.min = -3;
	act.max = 3;
	if (axis == 1)
		act.axis = &obj1->ori.x;
	else if (axis == 2)
		act.axis = &obj1->ori.y;
	else if (axis == 3)
		act.axis = &obj1->ori.z;
	return (act);
}
