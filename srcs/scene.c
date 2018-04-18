/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:22:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/10 19:33:46 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene(t_b *b)
{
	t_obj	*obj;

	b->cam.pos = init_vect(0.0, 0.0, -20);
	b->amb = init_col(0.1, 0.1, 0.1);
	add_lux(b, init_lux(init_vect(0., 0., -1.), init_col(0.7, 0.7, 0.7),
		init_col(1.0, 1.0, 1.0)));
	obj = add_obj(b, init_plane(init_vect(0., 1., 1.), -2.0, init_col(0., 0., 0.)));
	obj->tex.reflect = 1.0;
	obj->tex.rug = 20;
	obj->tex.plasti = 0.0;
	obj->tex.kd = init_col(0., 0., 0.);
	obj = add_obj(b, init_plane(init_vect(0., -1., 1.), -2.0, init_col(0., 0., 1.)));
	obj = add_obj(b, init_plane(init_vect(1., 0., 0.), 2.0, init_col(0., 1., 0.)));
	obj = add_obj(b, init_plane(init_vect(1., 0., 0.), -2.0, init_col(1., 1., 0.)));
	obj = add_obj(b, init_plane(init_vect(0., 0., 1.), 22.0, init_col(0., 1., 1.)));
	obj = add_obj(b, init_sph(init_vect(-2., 0., 0.), init_col(1., 0., 0.), 1.5));
	obj = b->obj;
}
