/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:03:06 by cquillet          #+#    #+#             */
/*   Updated: 2018/04/17 22:21:20 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		color_calc(t_col *col, t_lux *lux, t_b *b, t_v eye_to_obj)
{
	calc_atn(lux, b->inter.dist);
	vect_normalize(&lux->light);
	*col = color_add(*col, calc_dif(lux, b->inter));
	*col = color_add(*col, calc_spe(lux, b->inter, eye_to_obj));
}

/*
** Return the color
*/

t_col			cast_ray(t_b *b, t_ray ray, unsigned int depth)
{
	t_col			col;
	t_lux			*lux;

	b->inter.dist += vect_norme(vect_sub(ray.ori, ray2vect(ray)));
	if (!depth || ray.t > b->max - MARGIN_FLOAT || b->inter.dist > b->max_dist)
		return (init_col(0.0, 0.0, 0.0));
//	printf("cast_ray\n");
//	printf("cast_ray\nr=%.1f\ng=%.1f\nb=%.1f\n\n", b->inter.col.r, b->inter.col.g, b->inter.col.b);
	col = calc_amb(b);
//	b->inter.to_lux.ori = vect_add(ray2vect(ray), vect_multnb(&b->inter.n, 3.));
	b->inter.to_lux.ori = ray2vect(ray);
	vect_normalize(&ray.dir);
	lux = b->lux;
	while (lux)
	{
		b->inter.to_lux.dir = vect_sub(lux->ori, b->inter.to_lux.ori);
		if (vect_dot(b->inter.to_lux.dir, b->inter.n) > 0. &&
										!inter_obj_lux(b, &b->inter.to_lux))
		{
			lux->light = b->inter.to_lux.dir;
			color_calc(&col, lux, b, ray.dir);
		}
		lux = lux->next;
	}
	if (b->inter.tex.reflect > MARGIN_FLOAT)
		col = color_add(col, cast_reflect(b, ray, depth));
	color_max(&col, &b->colmax);
//	printf("cast_ray\nr=%.1f\ng=%.1f\nb=%.1f\n\n", col.r, col.g, col.b);
	return (col);
}

t_col			cast_reflect(t_b *b, t_ray ray, unsigned int depth)
{
	t_ray			refl;

	refl.ori = b->inter.to_lux.ori;
	refl.dir = reflect(ray.dir, b->inter.n);
	refl.t = b->max;
	refl.id = ray.id;
	inter_obj(b, &refl);
	if (b->inter.tex.reflect > 1.0 - MARGIN_FLOAT)
	{
		return (cast_ray(b, refl, depth));
	}
	return (color_multnb(cast_ray(b, refl, depth - 1), b->inter.tex.reflect));
};
