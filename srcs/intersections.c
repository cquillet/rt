/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:49:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/18 19:50:55 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	double	m;
	t_v		h;

	if ((b->inter.id = inter_all(b, ray, 1.0, LIGHT_RAY)) >= 0)
	{
		obj = search_obj(b, b->inter.id);
		b->inter.tex = obj->tex;
		if (obj->form == 1)
			b->inter.n = init_vect(obj->a, obj->b, obj->c);
		else if (obj->form <= 4)
			b->inter.n = vect_sub(ray2vect(*ray), obj->ori);
		if (obj->form == 3 || obj->form == 4)
		{
			h = obj->h;
			vect_normalize(&h);
			m = vect_dot(b->inter.n, h);
			if (obj->form == 4)
				m *= (1.0 + pow(tan(obj->angle), 2.0));
			b->inter.n = vect_sub(b->inter.n, vect_multnb(&h, m));
		}
		if (vect_dot(b->inter.n, ray->dir) > 0.0)
			b->inter.n = vect_multnb(&b->inter.n, -1);
	}
	return (ray->t);
}

/*
** Check intersection between impact and the lights
*/

int		inter_obj_lux(t_b *b, t_ray *to_light)
{
	to_light->t = 1.0;
	vect_normalize(&to_light->dir);
	return (inter_all(b, to_light, 2 * MARGIN_FLOAT, SHADOW_RAY));
}

/*
** inter for everything
*/

int		inter_all(t_b *b, t_ray *ray, double min, char shadow_ray)
{
	t_obj			*l;
	double			t;
	int				id;

	l = b->obj;
	id = -1;
	t = b->max;
	while (l)
	{
		if (l->form == 1)
			t = calc_plane(ray, *l, min);
		else if (l->form == 2)
			t = calc_sphere(ray, *l, min);
		else if (l->form == 3)
			t = calc_cyl(ray, *l, min);
		else if (l->form == 4)
			t = calc_cone(ray, *l, min);
		if (t > min && t < b->max && t < ray->t + MARGIN_FLOAT)
		{
//			if (t < ray->t - 2 * MARGIN_FLOAT)
				id = l->id;
/*			else if (l->id > id)
			{
				id = l->id;
				id = -1;
			}*/
			ray->t = t;
			if (flag == SHADOW_RAY)
				return (id);
		}
		l = l->next;
	}
	return (id);
}
