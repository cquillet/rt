/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:22:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/04 17:27:25 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene(t_b *b)
{
	t_obj	*obj;
	t_act	*act;

	b->cam.pos = init_vect(0.0, 0.0, -15);
	add_lux(b, init_lux(init_vect(1.0, 2.0, -15.0), init_col(1.0, 1.0, 1.0),
		init_col(1.0, 1.0, 1.0)));
	b->lux->dif = init_col(1.0, 1.0, 1.0);
	b->lux->spe = init_col(1.0, 1.0, 1.0);
	add_lux(b, init_lux(init_vect(-1.0, -2.0, -15.0), init_col(0.7, 0.7, 0.7),
		init_col(0.5, 0.5, 0.5)));
	b->lux->next->dif = init_col(1.0, 0.0, 1.0);
	b->lux->next->spe = init_col(1.0, 0.0, 1.0);
	add_obj(b, init_sph(init_vect(0.0, 0.0, -8.0), init_col(COL_WHITE), 1.0));
	obj = b->obj;
	add_action(b, init_act(obj, 2, 3));
	act = b->act;
	act->max = 8;
	act->min = -8;
	add_obj(b, init_sph(init_vect(0., 0., 0.), init_col(COL_WHITE), 0.5));
	add_obj(b, init_sph(init_vect(0.0, 2.0, 0.0),
		init_col(COL_NAVAJOWHITE), 1.5));
	add_obj(b, init_sph(init_vect(0.0, -2.0, 0.0),
		init_col(COL_NAVAJOWHITE), 1.5));
	add_obj(b, init_plane(init_vect(1., 0., 0.), 2.0, init_col(1., 1., 1.)));
	b->amb = init_col(0.2, 0.2, 0.2);
}
