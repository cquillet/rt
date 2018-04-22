/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:27:30 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/22 17:15:47 by cquillet         ###   ########.fr       */
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
	plane.r = 0;
	plane.h = init_vect(0.0, 0.0, 0.0);
	plane.ori = init_vect(0.0, 0.0, 0.0);
	plane.angle = 0;
	plane.tex = init_tex();
	plane.tex.ks = init_col(0.6, 0.6, 0.6);
	plane.tex.kd = init_col(0.7, 0.7, 0.7);
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
	if (r < 0.01)
		r = 0.1;
	else
		sph.r = r;
	sph.ori = v;
	sph.angle = 0;
	sph.h = init_vect(0.0, 0.0, 0.0);
	sph.tex = init_tex();
	sph.tex.ks = init_col(1.0, 1.0, 1.0);
	sph.tex.kd = init_col(1.0, 1.0, 1.0);
	sph.tex.col = (!col2int(col)) ? init_col(1.0, 1.0, 1.0) : col;
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
	cone.h = h;
	cone.tex = init_tex();
	cone.tex.ks = init_col(1.0, 1.0, 1.0);
	cone.tex.kd = init_col(1.0, 1.0, 1.0);
	cone.tex.col = (!col2int(col)) ? init_col(1.0, 1.0, 1.0) : col;
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
	if (r < 0.01)
		r = 0.1;
	cyl.r = r;
	cyl.h = h;
	cyl.ori = v;
	cyl.angle = 0;
	cyl.tex = init_tex();
	cyl.tex.ks = init_col(1.0, 1.0, 1.0);
	cyl.tex.kd = init_col(1.0, 1.0, 1.0);
	cyl.tex.col = (!col2int(col)) ? init_col(1.0, 1.0, 1.0) : col;
	cyl.next = NULL;
	return (cyl);
}
