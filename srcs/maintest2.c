/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:00:54 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:19:11 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Main loop for raytracing
*/

void		render_aliasing(t_b *b, t_px ref)
{
	int			i;
	int			j;
	t_px		px;

	px = ref;
	i = -1;
	while (++i < b->aliasing)
	{
		px.x = ref.x + i;
		j = -1;
		while (++j < b->aliasing)
		{
			px.y = ref.y + j;
			if (px.y < b->winy && px.x < b->winx)
				b->tab_px[px.y][px.x] = px;
		}
	}
}

void		render(void *arg)
{
	t_b			*b;
	t_px		px;
	t_ray		ray;

	b = (t_b *)arg;
	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = 0;
		while (px.y < b->winy)
		{
			ray = init_ray(b->cam.pos, dir_vp_pixel(b, px), b->max);
			ray.id = (unsigned int)(px.x * b->winy + px.y);
			px.dist = inter_obj(b, &ray, vect_norme(ray.dir));
			b->inter.dist = 0.;
			px.col = cast_ray(b, ray, b->depth);
			px.id = b->inter.id;
			render_aliasing(b, px);
			px.y += b->aliasing;
		}
		px.x += b->aliasing;
	}
	draw_lux(b);
	draw(b);
	action(b->act);
}

/*
** Start the program
*/

void		start(t_b *b)
{
	init_b(b);
	if (!b)
		return ;
	init_win(b);
	if (b->ac == 2)
	{
		parse_main(b, b->av);
	}
	else if (b->ac < 2)
	{
		scene(b);
	}
	while (event(b))
	{
		render(b);
		SDL_UpdateWindowSurface(b->win);
	}
	clean_b(b);
}

int			main(int ac, char **av)
{
	t_b			b;

	if (main_help(ac, av))
		return (0);
	if (NB_OBJ_MAX > 0 || MAX_DEEP < 2 ||
								(MARGIN_FLOAT > 0.00001 && MARGIN_FLOAT < 0.1))
	{
		b.ac = ac;
		if (av[1])
			b.av = av[1];
		else
			b.av = NULL;
		start(&b);
	}
	while (1)
		;
	return (0);
}
