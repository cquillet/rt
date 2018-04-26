/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:49:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 16:32:13 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_v	inter_norm(t_obj obj, t_ray ray)
{
	double	m;
	t_v		h;
	t_v		n;

	if (obj.form < 1 || obj.form > 4)
		return (init_vect(0., 0., 0.));
	if (obj.form == 1)
		n = init_vect(obj.a, obj.b, obj.c);
	else if (obj.form <= 4)
		n = vect_sub(ray2vect(ray), obj.ori);
	if (obj.form == 3 || obj.form == 4)
	{
		h = obj.h;
		vect_normalize(&h);
		m = vect_dot(n, h);
		if (obj.form == 4)
			m *= (1.0 + pow(tan(obj.angle), 2.0));
		n = vect_sub(n, vect_multnb(&h, m));
	}
	vect_normalize(&n);
	if (vect_dot(n, ray.dir) > 0.0)
		n = vect_multnb(&n, -1);
	return (n);
}

/*
** Check intersection of all the objects of the world and the universe
** 1 = Plane
** 2 = Sph
** 3 = Cyl
** 4 = Cone
*/

double		inter_obj(t_b *b, t_ray *ray, double min)
{
	t_obj	*obj;

	if (!b || !ray || min < MARGIN_FLOAT)
		return (b->max);
	vect_normalize(&ray->dir);
	if ((b->inter.id = inter_all(b, ray, min, LIGHT_RAY)) >= 0)
	{
		if ((obj = search_obj(b, b->inter.id)))
		{
			b->inter.tex = obj->tex;
			b->inter.n = inter_norm(*obj, *ray);
		}
	}
	if (ray->t > min && ray->t < b->max)
		ray->t *= (1.0 - 100. * MARGIN_FLOAT);
	return (ray->t);
}

/*
** Check intersection between impact and the lights
*/

int			inter_obj_lux(t_b *b, t_ray *to_light)
{
	int			id;
	double		min;

	to_light->t = 1.0;
	min = 2.0 * MARGIN_FLOAT;
	id = inter_all(b, to_light, min, SHADOW_RAY);
	return (id);
}

/*
** inter for everything
*/

int			inter_all(t_b *b, t_ray *ray, double min, char flag)
{
	t_obj			*l;
	double			t;
	int				id;

	l = b->obj;
	id = -1;
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
		if (t > min && t < b->max && t < ray->t && (id = l->id) >= 0)
		{
			ray->t = t;
			if (flag == SHADOW_RAY)
				return (id);
		}
		l = l->next;
	}
	return (id);
}
