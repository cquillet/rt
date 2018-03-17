/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lux_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:20:09 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 14:21:36 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Calculate the ambiant lux
*/

t_col	calc_amb(t_b *b)
{
	return (color_mult(b->amb, color_mult(b->inter.tex.ka, b->inter.tex.col)));
}

/*
** Calculate the diffuse lux
*/

void	calc_dif(t_lux *lux, t_inter inter)
{
	double	dot;

	if ((dot = vect_dot(inter.n, lux->light)) <= 0.0 || lux->atn <= 0.0)
		lux->lum_dif = init_col(0.0, 0.0, 0.0);
	else
		lux->lum_dif = color_mult(lux->dif,
		color_multnb(color_mult(inter.tex.kd, inter.tex.col), dot * lux->atn));
}

/*
** Calculate the specular lux
*/

void	calc_spe(t_lux *lux, t_inter inter, t_v to_eye)
{
	t_col	plasti;
	t_v		reflect;
	double	dot;

	if (lux->atn <= 0.0)
	{
		lux->lum_spe = init_col(0.0, 0.0, 0.0);
		return ;
	}
	reflect = vect_add(vect_multnb(&lux->light, -1),
		vect_multnb(&inter.n, 2 * vect_dot(lux->light, inter.n)));
	if ((dot = vect_dot(reflect, to_eye)) <= 0.0)
	{
		lux->lum_spe = init_col(0.0, 0.0, 0.0);
		return ;
	}
	plasti = color_add(color_multnb(inter.tex.col, 1 - inter.tex.plasti),
		init_col(inter.tex.plasti, inter.tex.plasti, inter.tex.plasti));
	lux->lum_spe = color_mult(lux->spe, color_multnb(color_mult(inter.tex.ks,
		plasti), pow(dot, inter.tex.rug) * lux->atn));
}

void	calc_atn(t_lux *lux, double dist)
{
	lux->atn = lux->amp_cst /
		(1.0 + lux->amp_lin * dist + lux->amp_quad * dist * dist);
	if (lux->atn < 0.0)
		lux->atn = 0.0;
}
