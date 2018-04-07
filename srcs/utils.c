/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:23:35 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/07 18:40:14 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Return the pos of the pixel in the viewplane
*/

t_v		dir_vp_upleft(t_b *b)
{
	b->vp.upleft = vect_add(
						vect_multnb(&b->cam.dir, b->vp.dist),
						vect_add(
							vect_multnb(&b->cam.dirup, b->vp.h / 2),
							vect_multnb(&b->cam.dirright, -b->vp.w / 2)));
	return (b->vp.upleft);
}

t_v		dir_vp_pixel(t_b *b, t_px px)
{
	t_v		tmp;
	t_v		tmp2;
	t_v		tmp3;

	tmp = vect_multnb(&b->cam.dirright, b->vp.xi * (double)px.x);
	tmp2 = vect_multnb(&b->cam.dirup, b->vp.yi * (double)px.y);
	tmp3 = vect_add(dir_vp_upleft(b), vect_sub(tmp, tmp2));
	return (tmp3);
}

/*
** Sort un vect a partir d'un ray
*/

t_v		ray2vect(t_ray ray)
{
	return (vect_add(ray.ori, vect_multnb(&ray.dir, ray.t)));
}

/*
** Solve any 1st and 2nd degree equation
*/

double	solve_equation(double min, double a, double b, double c)
{
	double	ret;
	double	delta;

	if (-MARGIN_FLOAT < a && a < MARGIN_FLOAT)
		return (-MARGIN_FLOAT < b && b < MARGIN_FLOAT ? 0. : -c / b);
	if (((delta = b * b - 4. * a * c) <= -MARGIN_FLOAT))
		return (min);
	else if (delta < MARGIN_FLOAT)
		return (-b / 2 / a);
	ret = (-b - sqrt(delta)) / 2 / a;
	return (ret > min ? ret : ((-b + sqrt(delta)) / 2 / a));
}

/*
** return the position of a 3D obj on the viewplane
*/

t_px	pos2px(t_b *b, t_v v)
{
	t_px	px;
	t_ray	ray;
	double	n;

	ray.ori = v;
	ray.dir = vect_sub(v, b->cam.pos);
	v = ray2vect(ray);
	n = vect_dot(ray.dir, b->cam.dirright) / vect_dot(ray.dir, b->cam.dir);
	px.x = (int)(b->winx * (0.5 + n * b->vp.dist / b->vp.w));
	n = vect_dot(ray.dir, b->cam.dirup) / vect_dot(ray.dir, b->cam.dir);
	px.y = (int)(b->winy * (0.5 - n * b->vp.dist / b->vp.h));
	return (px);
}
