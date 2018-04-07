/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:32:08 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/06 19:48:20 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Vect init
*/

t_v			init_vect(double x, double y, double z)
{
	t_v	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/*
** Vect list init
*/

t_vl		init_vl(t_v v, int id)
{
	t_vl	vl;

	vl.v = v;
	vl.id = id;
	return (vl);
}

/*
**	Init the color struct
*/

t_col		init_col(double r, double g, double b)
{
	t_col	col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

/*
** Init for a matrice
*/

t_matrice	init_matrice(void)
{
	int			i;
	int			j;
	t_matrice	m;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			m.data[i][j] = 0.0;
	}
	return (m);
}

/*
** Init ray
*/

t_ray		init_ray(t_v ori, t_v dir, double t)
{
	t_ray	ray;

	ray.ori = ori;
	ray.dir = dir;
	ray.t = t;
	return (ray);
}
