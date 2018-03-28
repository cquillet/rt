/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:58:03 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/23 17:41:13 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Return the color
*/

t_col			cast_ray(t_b *b, t_ray ray)
{
	t_col			col;
	t_lux			*lux;
	t_ray			to_l;

	if (ray.t >= b->max)
		return (init_col(0.0, 0.0, 0.0));
	lux = b->lux;
	col = calc_amb(b);
	to_l.ori = ray2vect(ray);
	vect_normalize(&ray.dir);
	while (lux)
	{
		to_l.dir = vect_sub(lux->ori, to_l.ori);
		if (vect_dot(to_l.dir, b->inter.n) > 0. && inter_obj_lux(b, &to_l) < 0)
		{
			lux->light = to_l.dir;
			calc_atn(lux, vect_norme(lux->light));
			vect_normalize(&lux->light);
			col = color_add(col, calc_dif(lux, b->inter));
			col = color_add(col, calc_spe(lux, b->inter, ray.dir));
		}
		lux = lux->next;
	}
	color_max(&col, &b->colmax);
	return (col);
}

/*
** Saturate the color
*/

void			color_sat(t_col *col)
{
	if (col->r > 1.0)
		col->r = 1.0;
	else if (col->r < 0.0)
		col->r = 0.0;
	if (col->g > 1.0)
		col->g = 1.0;
	else if (col->g < 0.0)
		col->g = 0.0;
	if (col->b > 1.0)
		col->b = 1.0;
	else if (col->b < 0.0)
		col->b = 0.0;
}

void			color_max(t_col *col, double *colmax)
{
	if (col->r < 0.0)
		col->r = 0.0;
	else if (col->r > *colmax)
		*colmax = col->r;
	if (col->g < 0.0)
		col->g = 0.0;
	else if (col->g > *colmax)
		*colmax = col->g;
	if (col->b < 0.0)
		col->b = 0.0;
	else if (col->b > *colmax)
		*colmax = col->b;
}

/*
** Gamma correction = coeff * (col ^ gamma)
*/

t_col			gamma_corr(t_col col, double coeff, double gamma)
{
	return (color_multnb(color_pow(col, gamma), coeff));
}
