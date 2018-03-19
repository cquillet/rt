/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sheit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:38:45 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/19 19:26:02 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** VERY important function to INITIALIZE the inter min at 666666666
*/

void	init_inter(t_inter *inter)
{
	inter = (t_inter *)malloc(sizeof(t_inter));
	inter->min = 666666666;
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

	tex.rug = 1.;
	tex.plasti = 0.;
	tex.refra = 0.;
	tex.trans = 0.;
	tex.hidden = 0;
	tex.reflect = 0.;
	tex.col = init_col(1.0, 1.0, 1.0);
	tex.ka = init_col(0.0, 0.0, 0.0);
	tex.kd = init_col(1.0, 1.0, 1.0);
	tex.ks = init_col(1.0, 1.0, 1.0);
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
