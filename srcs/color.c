/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:58:03 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/12 07:46:20 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Return the color
*/

t_col			get_color(t_b *b, t_ray ray)
{
	t_col			col;
	t_lux			*lux;
	t_ray			to_light;

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
			col = color_add(col, calc_dif(lux, b->inter));
			col = color_add(col, calc_spe(lux, b->inter, ray.dir));
		}
		lux = lux->next;
	}
	color_max(&col, &b->colmax);
	return (col);
}

/*
** Add 2 colors and return the result
*/

t_col			color_add(t_col col, t_col col2)
{
	t_col			tmp;

	tmp.r = col.r + col2.r;
	tmp.g = col.g + col2.g;
	tmp.b = col.b + col2.b;
	return (tmp);
}

/*
** Multiply 2 colors and return the result
*/

t_col			color_mult(t_col col, t_col col2)
{
	t_col			tmp;

	tmp.r = col.r * col2.r;
	tmp.g = col.g * col2.g;
	tmp.b = col.b * col2.b;
	return (tmp);
}

/*
** Multiply a color by nb
*/

t_col			color_multnb(t_col col, double nb)
{
	t_col			tmp;

	tmp.r = col.r * nb;
	tmp.g = col.g * nb;
	tmp.b = col.b * nb;
	return (tmp);
}

/*
** return the result of a color power n
*/

t_col			color_pow(t_col col, double n)
{
	t_col			tmp;

	tmp.r = pow(col.r, n);
	tmp.g = pow(col.g, n);
	tmp.b = pow(col.b, n);
	return (tmp);
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

/*
** Convert a t_col to an unsigned int color
*/

unsigned int	col2int(t_col col)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = 0xff & (unsigned int)(col.r * 255.0);
	g = 0xff & (unsigned int)(col.g * 255.0);
	b = 0xff & (unsigned int)(col.b * 255.0);
	return ((r << 16) | (g << 8) | b);
}

t_col			int2col(unsigned int color)
{
	t_col			col;

	col.r = ((double)((color >> 16) & 255)) / 255.0;
	col.g = ((double)((color >> 8) & 255)) / 255.0;
	col.b = ((double)((color) & 255)) / 255.0;
	return (col);
}
