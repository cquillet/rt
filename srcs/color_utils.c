/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:05:15 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 20:36:33 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Convert a t_col to an unsigned int color
*/

unsigned int	col2int(t_col col)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(col.r * 255.0);
	g = (unsigned int)(col.g * 255.0);
	b = (unsigned int)(col.b * 255.0);
	return ((r << 16) | (g << 8) | b);
}

/*
** Convert an int to a t_col
*/

t_col			int2col(unsigned int color)
{
	t_col col;

	col.r = ((double)((color >> 16) & 255)) / 255.0;
	col.g = ((double)((color >> 8) & 255)) / 255.0;
	col.b = ((double)((color) & 255)) / 255.0;
	return (col);
}
