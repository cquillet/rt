/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:03:06 by cquillet          #+#    #+#             */
/*   Updated: 2018/04/11 19:56:53 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
/*
 ** Return the color
 */

static void		color_calc(t_col *col, t_lux *lux, t_b *b, t_v eye_to_obj)
{
	calc_atn(lux, b->inter.dist);
	vect_normalize(&lux->light);
	*col = color_add(*col, calc_dif(lux, b->inter));
	*col = color_add(*col, calc_spe(lux, b->inter, eye_to_obj));
}

t_col			cast_ray(t_b *b, t_ray ray, unsigned int depth)
{
	t_col			col;
	t_lux			*lux;

	b->inter.dist += vect_norme(vect_sub(ray.ori, ray2vect(ray)));
//	printf("ray.id=%u\n", ray.id % b->winx);
	if (ray.id > b->winy * b->winx * 3 / 4)
		printf("\nid = %d\ndepth=%u\nt=%f\nmax=%f\ndist=%f\nmax_dist=%f\n", ray.id, depth, ray.t, b->max, b->inter.dist, b->max_dist);
	if (!depth || ray.t > b->max - MARGIN_FLOAT || b->inter.dist > b->max_dist)
		return (init_col(0.0, 0.0, 0.0));
	col = calc_amb(b);
	b->inter.to_lux.ori = ray2vect(ray);
	vect_normalize(&ray.dir);
	lux = b->lux;
	while (lux)
	{
		b->inter.to_lux.dir = vect_sub(lux->ori, b->inter.to_lux.ori);
		if (vect_dot(b->inter.to_lux.dir, b->inter.n) > 0. &&
				inter_obj_lux(b, &b->inter.to_lux) < 0)
		{
			lux->light = b->inter.to_lux.dir;
			color_calc(&col, lux, b, ray.dir);
		}
		lux = lux->next;
	}
	if (ray.id > b->winy * b->winx * 3 / 4)
		printf("col avant refl:\nr=%f\ng=%f\nb=%f\n", col.r, col.g, col.b);
	if (b->inter.tex.reflect >  MARGIN_FLOAT)
		col = color_add(col, cast_reflect(b, ray, depth));
	color_max(&col, &b->colmax);
	if (ray.id > b->winy * b->winx * 3 / 4)
		printf("col apres refl:\nr=%f\ng=%f\nb=%f\n\n", col.r, col.g, col.b);
	return (col);
}

/*int SDL_RenderDrawLine(SDL_Renderer* renderer,
		int           x1,
		int           y1,
		int           x2,
		int           y2)*/

t_col			cast_reflect(t_b *b, t_ray ray, unsigned int depth)
{
	t_ray			refl;

	if (ray.id > b->winy * b->winx * 3 / 4)
		printf("refl_");
	refl.ori = b->inter.to_lux.ori;
	refl.dir = reflect(ray.dir, b->inter.n);
	refl.t = b->max;
	refl.id = ray.id;
	inter_obj(b, &refl);
	if (b->inter.tex.reflect > 1.0 - MARGIN_FLOAT)
	{
	if (ray.id > b->winy * b->winx * 3 / 4)
			printf("totale\n");
		return (cast_ray(b, refl, depth));
	}
	if (ray.id > b->winy * b->winx * 3 / 4)
			printf("partielle %f\n", b->inter.tex.reflect);
	return (color_multnb(cast_ray(b, refl, depth - 1), b->inter.tex.reflect));
};
