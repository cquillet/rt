/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:00:15 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/07 19:55:22 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sort le carré de la norme du vecteur
*/

double		vect_norme2(t_v v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/*
** Sort la norme du vecteur
*/

double		vect_norme(t_v v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

/*
** Normalize a vector
*/

void		vect_normalize(t_v *v)
{
	double n;

	n = vect_norme(*v);
	if (-MARGIN_FLOAT < n && n < MARGIN_FLOAT)
	{
		v->x = 0.;
		v->y = 0.;
		v->z = 0.;
	}
	else
	{
		v->x /= n;
		v->y /= n;
		v->z /= n;
	}
}

t_v			reflect(t_v v, t_v n)
{
	return (vect_add(vect_multnb(&v, -1), vect_multnb(&n, 2 * vect_dot(v, n))));
}

/*
** Rotate a vector
*/

t_v			vect_rotate(t_v v, double angle, t_v axe)
{
	t_v			tmp;
	t_matrice	q;
	t_matrice	r;

	q = init_matrice();
	r = init_matrice();
	q.data[0][1] = -axe.z;
	q.data[0][2] = axe.y;
	q.data[1][0] = axe.z;
	q.data[1][2] = -axe.x;
	q.data[2][0] = -axe.y;
	q.data[2][1] = axe.x;
	r.data[0][0] = 1;
	r.data[1][1] = 1;
	r.data[2][2] = 1;
	r = matrice_add(r, matrice_multnb(q, sin(angle)));
	r = matrice_add(r, matrice_multnb(matrice_mult(q, q), 1 - cos(angle)));
	tmp = matrice_multvect(r, v);
	return (tmp);
}
