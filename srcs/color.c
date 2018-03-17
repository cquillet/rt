/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:58:03 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 15:15:48 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

unsigned int	spectrum_color(int value, int min, int max)
{
	int		c;

	c = (value - min) * 0xffffff / (max - min);
	if (c < 0xFF)
		return (0xFF00FE - c);
	if (c < 0x1FE)
		return (0xFF0100 + ((c - 0xFF) << 8));
	if (c < 0x2FD)
		return (0xFEFF00 - ((c - 0x1FE) << 16));
	if (c < 0x3FC)
		return (0x00FF01 + (c - 0x2FD));
	if (c < 0x4FB)
		return (0x00FEFF - ((c - 0x3FC) << 8));
	return (0x0100FF + ((c - 0x4FB) << 16));
}

/*
** Return the color
*/

t_col			get_color(t_b *b, t_ray ray)
{
	t_col		col;
	t_lux		*lux;
	t_ray		to_light;

	if (ray.t >= b->max - MARGIN_FLOAT)
		return (init_col(0.0, 0.0, 0.0));
	lux = b->lux;
	col = calc_amb(b);
	to_light.ori = ray2vect(ray);
	vect_normalize(&ray.dir);
	while (lux)
	{
		to_light.dir = vect_sub(lux->ori, to_light.ori);
		if (vect_dot(to_light.dir, b->inter.n) > 0. && inter_obj_lux(b, &to_light) < 0)
		{
			lux->light = to_light.dir;
			calc_atn(lux, vect_norme(lux->light));
			vect_normalize(&lux->light);
			calc_dif(lux, b->inter);
			col = color_add(col, lux->lum_dif);
			calc_spe(lux, b->inter, vect_multnb(&ray.dir, -1));
			col = color_add(col, lux->lum_spe);
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

t_col	gamma_corr(t_col col, double coeff, double gamma)
{
	return (color_multnb(color_pow(col, gamma), coeff));
}
