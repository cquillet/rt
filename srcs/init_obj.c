/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:27:30 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/23 16:51:46 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Init for the plane
*/

t_obj		init_plane(t_v n, double d, t_col col)
{
	t_obj plane;

	plane.form = 1;
	plane.a = n.x;
	plane.b = n.y;
	plane.c = n.z;
	plane.d = d;
	if (!n.x && !n.y && !n.z)
		plane.b = 1.0;
	plane.r = 0.;
	plane.h = init_vect(0.0, 0.0, 0.0);
	plane.ori = init_vect(0.0, 0.0, 0.0);
	plane.angle = 0.;
	plane.tex = init_tex();
	plane.tex.col = col;
	plane.next = NULL;
	return (plane);
}

/*
** Init plane V2.0 the return of the comeback
*/

t_obj		init_plane2(t_v ori, t_v h, t_v w)
{
	t_v		n;
	t_obj	p;

	n = vect_prod(w, h);
	vect_normalize(&n);
	p = init_plane(n, -vect_dot(n, ori), init_col(1.0, 1.0, 1.0));
	return (p);
}

/*
** Init for sphere
*/

t_obj		init_sph(t_v v, t_col col, double r)
{
	t_obj	sph;

	sph.form = 2;
	sph.a = 0;
	sph.b = 0;
	sph.c = 0;
	sph.d = 0;
	if (r < 0.5)
		r = 0.5;
	sph.r = r;
	sph.ori = v;
	sph.angle = 0;
	sph.h = init_vect(0.0, 0.0, 0.0);
	sph.tex = init_tex();
	sph.tex.col = col;
	sph.next = NULL;
	return (sph);
}

/*
** Init for cone
*/

t_obj		init_cone(t_v v, t_col col, t_v h, double angle)
{
	t_obj	cone;

	cone.form = 4;
	cone.a = 0;
	cone.b = 0;
	cone.c = 0;
	cone.d = 0;
	cone.r = 0;
	cone.ori = v;
	if (angle < 1.)
		angle = 1.;
	else if (angle > 89.)
		angle = 89.;
	cone.angle = DEG2RAD(angle);
	if (vect_norme2(h) < MARGIN_FLOAT)
		cone.h = init_vect(0.0, 0.1, 0.0);
	else
		cone.h = h;
	cone.tex = init_tex();
	cone.tex.col = col;
	cone.next = NULL;
	return (cone);
}

/*
** Init for cylindre
*/

t_obj		init_cyl(t_v v, t_col col, t_v h, double r)
{
	t_obj cyl;

	cyl.form = 3;
	cyl.a = 0;
	cyl.b = 0;
	cyl.c = 0;
	cyl.d = 0;
	if (r < 0.5)
		r = 0.5;
	cyl.r = r;
	if (vect_norme2(h) < MARGIN_FLOAT)
		cyl.h = init_vect(0.0, 0.1, 0.0);
	else
		cyl.h = h;
	cyl.ori = v;
	cyl.angle = 0;
	cyl.tex = init_tex();
	cyl.tex.col = col;
	cyl.next = NULL;
	return (cyl);
}
