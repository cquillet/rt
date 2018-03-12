/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:00:54 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/12 06:28:35 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
**	Basic draw
*/

void		ray_cast(t_b *b, t_px *px, t_ray *ray)
{
	int			i;
	int			j;

	inter_obj(b, ray);
	px->col = get_color(b, *ray);
	i = -1;
	while (++i < b->aliasing)
	{
		j = -1;
		while (++j < b->aliasing)
		{
			if (px->y + j < b->winy && px->x + i < b->winx)
			{
				b->tab_px[px->y + j][px->x + i] = *px;
				b->tab_px[px->y + j][px->x + i].dist = ray->t;
				b->tab_px[px->y + j][px->x + i].id = b->inter.id;
			}
		}
	}
}

void		render(t_b *b)
{
	t_px		px;
	t_ray		ray;

	b->colmax = 0.;
	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = 0;
		while (px.y < b->winy)
		{
			ray = init_ray(b->cam.pos, dir_vp_pixel(b, px), b->max);
			b->tab_px[px.y][px.x] = px;
			ray_cast(b, &b->tab_px[px.y][px.x], &ray);
			px.y += b->aliasing;
		}
		px.x += b->aliasing;
	}
	draw_lux(b);
	draw(b);
	action(b->act);
	SDL_UpdateWindowSurface(b->win);
}


int			main(int ac, char **av)
{
	t_b			b;

	if (main_help(ac, av[1]))
		return (EXIT_SUCCESS);
	else if (ac == 2)
	{
		parse_main(&b, av[1]);
		init_b(&b);
	}
	else if (ac < 2)
	{
		init_b(&b);
		init_win(&b);
		scene2(&b);
	}
	init_win(&b);
	print_obj(b.obj);
	while (event(&b))
		render(&b);
	SDL_DestroyWindow(b.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
