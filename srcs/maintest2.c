/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:00:54 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/21 14:48:07 by cquillet         ###   ########.fr       */
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
//	b->colmax = 0.;
	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = b->y;
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
	if (b->ac == 2)
	{
		init_b(b);
		init_win(b);
		parse_main(b, b->av);
	}
	else if (b->ac < 2)
	{
		init_b(b);
		init_win(b);
		scene(b);
	}
	while (event(b))
	{
		render(b);
		SDL_UpdateWindowSurface(b->win);
		if (b->rec)
			ev_screenshot(b);
	}
	SDL_DestroyWindow(b->win);
	SDL_Quit();
}

int			main(int ac, char **av)
{
	t_b			b;

	if (main_help(ac, av))
		return (0);
	b.ac = ac;
	b.av = av[1];
	b.rec = 0;
	start(&b);
	return (0);
}
