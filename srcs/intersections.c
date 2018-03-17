/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:49:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 15:26:08 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Check intersection of all the objects of the world and the universe
** 1 = Plane
** 2 = Sph
** 3 = Cyl
** 4 = Cone
*/

double	inter_obj(t_b *b, t_ray *ray)
{
	t_obj	*obj;
	int		id;
	double	m;
	t_v		h;

	if ((id = inter_all(b, ray, 1.0)) > 0)
	{
		b->inter.id = id;
		obj = search_obj(b, b->inter.id);
		if (obj->form == 1)
			b->inter.n = init_vect(obj->a, obj->b, obj->c);
		else if (obj->form == 2)
			b->inter.n = vect_sub(ray2vect(*ray), obj->ori);
		else if (obj->form == 3)
		{
			h = obj->h;
			vect_normalize(&h);
			m = vect_dot(ray->dir, h) * ray->t + vect_dot(vect_sub(ray->ori, obj->ori), h);
			b->inter.n = vect_sub(ray2vect(*ray), vect_add(obj->ori, vect_multnb(&h, m)));
		}
		else if (obj->form == 4)
		{
			h = obj->h;
			vect_normalize(&h);
			m = (vect_dot(ray->dir, h) * ray->t + vect_dot(vect_sub(ray->ori, obj->ori), h)) * (1.0 + pow(tan(obj->angle), 2.0));
			b->inter.n = vect_sub(ray2vect(*ray), vect_add(obj->ori, vect_multnb(&h, m)));
		}
		if (vect_dot(b->inter.n, ray->dir) > 0.0)
			b->inter.n = vect_multnb(&b->inter.n, -1);
		b->inter.tex = obj->tex;
	}
	return (ray->t);
}

/*
** Check intersction of all the objects of the world and the universe and not clement
*/

int	inter_obj_lux(t_b *b, t_ray *to_light)
{
	to_light->t = 1.0;
	return (inter_all(b, to_light, MARGIN_FLOAT));
}

/*
** inter for everything
*/

int		inter_all(t_b *b, t_ray *ray, double min)
{
	t_obj			*l;
	double			t;
	unsigned int	id;

	l = b->obj;
	id = -1;
	while (l)
	{
		t = b->max;
		if (l->form == 1)
			t = calc_plane(ray, *l, min);
		else if (l->form == 2)
			t = calc_sphere(ray, *l, min);
		else if (l->form == 3)
			t = calc_cyl(ray, *l, min);
		else if (l->form == 4)
			t = calc_cone(ray, *l, min);
		if (t > min && t < ray->t)
		{
			ray->t = t;
			id = l->id;
		}
		l = l->next;
	}
	return (id);
}
