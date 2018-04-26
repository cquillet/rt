/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:05:58 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 20:14:30 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Calculate the intersection between a ray and a spherical sphere
*/

double		calc_sphere(t_ray *ray, t_obj sph, double min)
{
	double	ret;
	t_v		ori;

	ori = vect_sub(ray->ori, sph.ori);
	ret = solve_equation(min, vect_norme2(ray->dir),
				2 * vect_dot(ray->dir, ori), vect_norme2(ori) - sph.r * sph.r);
	return (ret);
}

/*
** Calculate the intersection between a ray and a planical plane
*/

double		calc_plane(t_ray *ray, t_obj plane, double min)
{
	double	prod;
	double	r;
	t_v		n;

	n = init_vect(plane.a, plane.b, plane.c);
	prod = vect_dot(n, ray->dir);
	if (!prod)
		return (-1.);
	r = -(vect_dot(n, ray->ori) + plane.d) / prod;
	if (r < min)
		return (-1.);
	return (r);
}

/*
** Calulate the intersection for cylindre
*/

double		calc_cyl(t_ray *ray, t_obj cyl, double min)
{
	double	coeff[3];
	double	dot[2];
	t_v		ori;
	t_v		h;

	ori = vect_sub(ray->ori, cyl.ori);
	h = cyl.h;
	vect_normalize(&h);
	dot[0] = vect_dot(ray->dir, h);
	dot[1] = vect_dot(ori, h);
	coeff[0] = vect_norme2(ray->dir) - dot[0] * dot[0];
	coeff[1] = 2 * (vect_dot(ray->dir, ori) - dot[0] * dot[1]);
	coeff[2] = vect_norme2(ori) - dot[1] * dot[1] - cyl.r * cyl.r;
	return (solve_equation(min, coeff[0], coeff[1], coeff[2]));
}

/*
** Calculate the intersection between a ray and a conerical cone
*/

double		calc_cone(t_ray *ray, t_obj cone, double min)
{
	double	coeff[3];
	double	dot[2];
	double	k;
	double	t;
	t_v		ori;

	ori = vect_sub(ray->ori, cone.ori);
	vect_normalize(&cone.h);
	dot[0] = vect_dot(ray->dir, cone.h);
	dot[1] = vect_dot(ori, cone.h);
	k = 1.0 + pow(tan(cone.angle), 2.0);
	coeff[0] = vect_norme2(ray->dir) - k * dot[0] * dot[0];
	coeff[1] = 2.0 * (vect_dot(ray->dir, ori) - k * dot[0] * dot[1]);
	coeff[2] = vect_norme2(ori) - k * dot[1] * dot[1];
	t = solve_equation(min, coeff[0], coeff[1], coeff[2]);
	if (vect_dot(cone.h, vect_sub(vect_add(ray->ori,
								vect_multnb(&ray->dir, t)), cone.ori)) < 0.)
		return (ray->t);
	return (t);
}
