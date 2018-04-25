/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:11:32 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/03 17:10:35 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Add 2 colors and return the result
*/

t_col		color_add(t_col col, t_col col2)
{
	t_col tmp;

	tmp.r = col.r + col2.r;
	tmp.g = col.g + col2.g;
	tmp.b = col.b + col2.b;
	return (tmp);
}

/*
** Multiply 2 colors and return the result
*/

t_col		color_mult(t_col col, t_col col2)
{
	t_col tmp;

	tmp.r = col.r * col2.r;
	tmp.g = col.g * col2.g;
	tmp.b = col.b * col2.b;
	return (tmp);
}

/*
** Multiply a color by nb
*/

t_col		color_multnb(t_col col, double nb)
{
	t_col tmp;

	tmp.r = col.r * nb;
	tmp.g = col.g * nb;
	tmp.b = col.b * nb;
	return (tmp);
}

/*
** return the result of a color power n
*/

t_col		color_pow(t_col col, double n)
{
	t_col tmp;

	tmp.r = pow(col.r, n);
	tmp.g = pow(col.g, n);
	tmp.b = pow(col.b, n);
	return (tmp);
}
