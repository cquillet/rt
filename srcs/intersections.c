/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:49:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/19 20:37:01 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v			inter_normale(t_obj obj, t_ray ray)
{
	t_v		n;
	double	m;

//					printf("inter_norm\n");
	n = init_vect(0., 0., 0.);
	if (obj.form < 1 || obj.form > 4)
		return (n);
	else if (obj.form == 1)
		n = init_vect(obj.a, obj.b, obj.c);
	else //if (obj.form <= 4)
		n = vect_sub(ray2vect(ray), obj.ori);
//					printf("inter_norm 2\n");
	if (obj.form == 3 || obj.form == 4)
	{
		vect_normalize(&obj.h);
		m = vect_dot(n, obj.h);
		if (obj.form == 4)
			m *= (1.0 + pow(tan(obj.angle), 2.0));
		n = vect_sub(n, vect_multnb(&obj.h, m));
	}
//					printf("inter_norm 3\n");
	vect_normalize(&n);
	if (vect_dot(n, ray.dir) > 0.0)
		n = vect_multnb(&n, -1);
//					printf("inter_norm 4\n");
	return (n);
}

/*
** Check intersection of all the objects of the world and the universe
** 1 = Plane
** 2 = Sph
** 3 = Cyl
** 4 = Cone
*/

double	inter_obj(t_b *b, t_ray *ray)
{
	t_obj		*obj;

	b->inter.n = init_vect(0., 0., 0.);
	b->inter.col = init_col(0., 0., 0.);
	b->inter.tex.ka = init_col(0., 0., 0.);
	if ((inter_all(b, ray, 1.0, LIGHT_RAY) > 0))
	{
			obj = search_obj(b, b->inter.id);
			if (obj)
			{
				b->inter.n = vect_add(b->inter.n, inter_normale(*obj, *ray));
				b->inter.col = color_add(b->inter.col, obj->tex.col);
				b->inter.tex.ka = color_add(b->inter.tex.ka, obj->tex.ka);
//				b->inter.tex.ks = color_add(b->inter.tex.ks, obj->tex.ks);
//				b->inter.tex.kd = color_add(b->inter.tex.kd, obj->tex.kd);
			}
//		printf("inter_obj fin liste\n");
		if (b->nb_inter > 1)
		{
//			b->inter.n = vect_multnb(&b->inter.n, 1. / (double)b->nb_inter);
//			b->inter.col = color_multnb(b->inter.col, 1. / (double)b->nb_inter);
//			b->inter.tex.ka = color_multnb(b->inter.tex.ka, 1. / (double)b->nb_inter);
			b->inter.tex.ks = init_col(0., 0., 0.);
			b->inter.tex.kd = init_col(0., 0., 0.);
//			b->inter.tex.ks = color_multnb(b->inter.tex.ks, 1. / (double)nb);
//			b->inter.tex.kd = color_multnb(b->inter.tex.kd, 1. / (double)nb);
//			printf("\tnb=%d\nn=(%f,\n%f,\n%f)\n\nr=%.1f\ng=%.1f\nb=%.1f\n\n", nb, b->inter.n.x, b->inter.n.y, b->inter.n.z, b->inter.col.r, b->inter.col.g, b->inter.col.b);
		}
		vect_normalize(&b->inter.n);
	}
	return (ray->t);
}

/*
** Check intersection between impact and the lights
*/

int		inter_obj_lux(t_b *b, t_ray *to_light)
{
//	t_list			*lst;

	to_light->t = 1.0;
/*	while (b->inter.multiple)
	{
		lst = (b->inter.multiple)->next;
//					printf("f1 %p\n", b->inter.multiple);
		if ((b->inter.multiple)->content)
//					{printf("f2 %p\n", (int *)(b->inter.multiple->content));
			free((b->inter.multiple)->content);
//					printf("f3\n");}
		if (b->inter.multiple)
//					{printf("f4\n");
			free(b->inter.multiple);
//					printf("f5\n");}
//					printf("f6\n");
		b->inter.multiple = lst;
	}*/
	inter_all(b, to_light, 2 * MARGIN_FLOAT, SHADOW_RAY);
	return (b->nb_inter);
}

/*
 ** inter for everything
 */

int			inter_all(t_b *b, t_ray *ray, double min, char flag)
{
	t_obj			*l;
	double			t;
	int				id;
//	t_list			*lst;

	l = b->obj;
	id = -1;
	t = b->max;
	b->nb_inter = 0;
//					printf("inter_all %p\n", b->inter.multiple);
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
		if (t > min && t < b->max && t < ray->t + 2 * MARGIN_FLOAT)
		{
			if (t < ray->t - 2 * MARGIN_FLOAT)
			{
				b->nb_inter = 0;
/*				while (b->inter.multiple)
				{
					lst = (b->inter.multiple)->next;
//					printf("f1 %p\n", b->inter.multiple);
					if ((b->inter.multiple)->content)
//					{printf("f2 %p\n", (int *)(b->inter.multiple->content));
						free((b->inter.multiple)->content);
//					printf("f3\n");}
					if (b->inter.multiple)
//					{printf("f4\n");
						free(b->inter.multiple);
//					printf("f5\n");}
//					printf("f6\n");
					b->inter.multiple = lst;
				}*/
//				ray->t = t;
			}
/*			else
			{
			printf("intersection %d (new) et %d (old)\n", l->id, id);
			}*/
//					printf("g1\n");
/*					if (!(b->inter.multiple))
						b->inter.multiple = ft_lstnew((void *)(&l->id), sizeof(int));
					else
					{
						lst = b->inter.multiple;
					//		ft_lstnew((void *)(&l->id), sizeof(int));
						while (lst->next)
						{
//							printf("lst %d\n", *(int *)(lst->content));
							lst = lst->next;
						}
			//		if (!b->inter.multiple)
			//			b->inter.multiple = lst;
			//		else
			//		{
			//			lst->next = b->inter.multiple;
			//			*(b->inter.multiple) = *lst;
			//		}
						lst->next = ft_lstnew((void *)(&l->id), sizeof(int));
					}*/
		/*	ft_lstadd(&b->inter.multiple,
									ft_lstnew((void *)(&l->id), sizeof(int)));*/
//					printf("g2\n");
			b->inter.tex = l->tex;
			b->inter.col = l->tex.col;
			b->inter.id = l->id;
			ray->t = t;
			b->nb_inter++;
			if (flag == SHADOW_RAY)
				return (b->nb_inter);
		}
		l = l->next;
	}
	return (b->nb_inter);
}
