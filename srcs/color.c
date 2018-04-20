/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:58:03 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/04 17:09:25 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Return the color
*/

static void		color_calc(t_col *col, t_lux *lux, t_b *b, t_v eye_to_obj)
{
	calc_atn(lux, vect_norme(lux->light));
	vect_normalize(&lux->light);
	*col = color_add(*col, calc_dif(lux, b->inter));
	*col = color_add(*col, calc_spe(lux, b->inter, eye_to_obj));
}

t_col			cast_ray(t_b *b, t_ray ray)
{
	t_col			col;
	t_lux			*lux;
	t_ray			to_l;

	if (ray.t > b->max - MARGIN_FLOAT)
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
			color_calc(&col, lux, b, ray.dir);
		}
		lux = lux->next;
	}
	color_max(&col, &b->colmax);
	return (col);
}

/*
** Saturate the color
*/

void			color_sat(t_col *col, double sat)
{
	if (sat < 1.0)
		sat = 1.0;
	if (col->r > sat)
		col->r = sat;
	else if (col->r < 0.0)
		col->r = 0.0;
	if (col->g > sat)
		col->g = sat;
	else if (col->g < 0.0)
		col->g = 0.0;
	if (col->b > sat)
		col->b = sat;
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
