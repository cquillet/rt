/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:03:06 by cquillet          #+#    #+#             */
/*   Updated: 2018/04/23 17:07:24 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Return the color
*/

static void		color_calc(t_col *col, t_lux *lux, t_b *b, t_v eye_to_obj)
{
	if (b && col && lux)
	{
		calc_atn(lux, b->inter.dist);
		vect_normalize(&lux->light);
		*col = color_add(*col, calc_dif(lux, b->inter));
		*col = color_add(*col, calc_spe(lux, b->inter, eye_to_obj));
	}
}

t_col			cast_ray(t_b *b, t_ray ray, unsigned int depth)
{
	t_col			col;
	t_lux			*lux;

	if (!b || !depth || ray.t > b->max - MARGIN_FLOAT ||
										(b->inter.dist += ray.t) > b->max_dist)
		return (init_col(0.0, 0.0, 0.0));
	col = calc_amb(b);
	b->inter.to_lux.ori = vect_add(ray2vect(ray),
								vect_multnb(&b->inter.n, 100. * MARGIN_FLOAT));
	lux = b->lux;
	while (lux)
	{
		b->inter.to_lux.dir = vect_sub(lux->ori, b->inter.to_lux.ori);
		if (vect_dot(b->inter.to_lux.dir, b->inter.n) > MARGIN_FLOAT &&
										inter_obj_lux(b, &b->inter.to_lux) < 0)
		{
			lux->light = b->inter.to_lux.dir;
			color_calc(&col, lux, b, ray.dir);
		}
		lux = lux->next;
	}
	if (b->inter.tex.reflect > MARGIN_FLOAT)
		col = color_add(col, cast_reflect(b, ray, depth - 1));
	color_max(&col, &b->colmax);
	return (col);
}

t_col			cast_reflect(t_b *b, t_ray ray, unsigned int depth)
{
	t_ray			refl;

	if (!b || !depth)
		return (init_col(0.0, 0.0, 0.0));
	refl.ori = b->inter.to_lux.ori;
	refl.dir = reflect(ray.dir, b->inter.n);
	refl.t = b->max;
	refl.id = ray.id;
	inter_obj(b, &refl, 2 * MARGIN_FLOAT);
	if (b->inter.tex.reflect > 1.0 - MARGIN_FLOAT)
		return (cast_ray(b, refl, depth));
	return (color_multnb(cast_ray(b, refl, depth), b->inter.tex.reflect));
}
