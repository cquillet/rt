/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 20:08:33 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/12 11:26:05 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Return the pos of the pixel in the viewplane
*/

t_v		dir_vp_upleft(t_b *b)
{
	b->vp.upleft = vect_add(
						vect_multnb(&b->cam.dir, b->vp.dist),
						vect_add(
							vect_multnb(&b->cam.dirup, b->vp.h / 2),
							vect_multnb(&b->cam.dirright, -b->vp.w / 2)));
	return (b->vp.upleft);
}

t_v		dir_vp_pixel(t_b *b, t_px px)
{
	t_v	tmp;
	t_v tmp2;
	t_v tmp3;

	tmp = vect_multnb(&b->cam.dirright, b->vp.xi * (double)px.x);
	tmp2 = vect_multnb(&b->cam.dirup, b->vp.yi * (double)px.y);
	tmp3 = vect_add(dir_vp_upleft(b), vect_sub(tmp, tmp2));
	return (tmp3);
}

/*
** Sort un vect a partir d'un ray
*/

t_v		ray2vect(t_ray ray)
{
	return (vect_add(ray.ori, vect_multnb(&ray.dir, ray.t)));
}

/*
** Solve any 1st and 2nd degree equation
*/

double		solve_equation(double min, double a, double b, double c)
{
	double	ret;
	double	delta;

	if (barely_zero(a))
		return (-c / b);
	else if (barely_zero((delta = b * b - 4 * a * c)))
		return (-b / 2 / a);
	else if (delta < 0.0)
		return (-1.);
	ret = (-b - sqrt(delta)) / 2 / a;
	if (ret > min)
		return (ret);
	else
		return ((-b + sqrt(delta)) / 2 / a);
}

/*
** return the position of a 3D obj on the viewplane
*/

t_px	pos2px(t_b *b, t_v v)
{
	t_px	px;
	t_ray	ray;
	double	n;

	ray.ori = v;
	ray.dir = vect_sub(v, b->cam.pos);
	v = ray2vect(ray);
	n = vect_dot(ray.dir, b->cam.dirright) / vect_dot(ray.dir, b->cam.dir);
	px.x = (int)(b->winx * (0.5 + n * b->vp.dist / b->vp.w));
	n = vect_dot(ray.dir, b->cam.dirup) / vect_dot(ray.dir, b->cam.dir);
	px.y = (int)(b->winy * (0.5 - n * b->vp.dist / b->vp.h));
	return (px);
}

/*
** Affiche toutes les caracteristiques d'un objet
*/

void	print_obj(t_obj *obj)
{
	ft_putendl("------------ PRINT OBJ ------------");
	printf("form = %d \n id = %d \n a = %f \n b = %f \n c = %f \n d = %f \n angle = %f \n",
		obj->form, obj->id, obj->a, obj->b, obj->c,obj->d, obj->angle);
	ft_putstr("h = ");
	vect_print(obj->h);
	ft_putstr("ori = ");
	vect_print(obj->ori);
	ft_putendl("-----------------------------------");
}


































