/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:58:03 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/21 14:02:04 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
