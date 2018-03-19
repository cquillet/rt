/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:00:54 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/19 19:19:36 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Main function for raytracing
*/

void		rt(t_b *b)
{
	t_px		px;
	t_ray		ray;
	t_col		col;
	int			i;
	int			j;

	b->colmax = 0.;
	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = 0;
		while (px.y < b->winy)
		{
			ray = init_ray(b->cam.pos, dir_vp_pixel(b, px), 0.);
			ray.t = b->max;
			inter_obj(b, &ray);
			col = get_color(b, ray);
			i = -1;
			while (++i < b->aliasing)
			{
				j = -1;
				while (++j < b->aliasing)
				{
					if (px.y + j < b->winy && px.x + i < b->winx)
					{
						b->tab_px[px.y + j][px.x + i] = px;
						b->tab_px[px.y + j][px.x + i].col = col;
						b->tab_px[px.y + j][px.x + i].dist = 30 - ray.t;
						b->tab_px[px.y + j][px.x + i].id = b->inter.id;
					}
				}
			}
			px.y += b->aliasing;
		}
		px.x += b->aliasing;
	}
	draw_lux(b);
	draw(b);
	action(b->act);
	SDL_UpdateWindowSurface(b->win);
}

void		draw(t_b *b)
{
	t_px		px;
	int			i;
	int			j;
	t_col		col;

	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = 0;
		while (px.y < b->winy)
		{
			i = -1;
			while (++i < b->aliasing)
			{
				j = -1;
				while (++j < b->aliasing)
				{
					if (px.y + j < b->winy && px.x + i < b->winx)
					{
						col = color_multnb(b->tab_px[px.y + j][px.x + i].col, 1 / b->colmax);
						col = gamma_corr(col, 1.0, b->gamma);
						SDL_LockSurface(b->img);
						*((unsigned int *)b->img->pixels + b->winx * (px.y + j) + px.x + i) = col2int(col);
						SDL_UnlockSurface(b->img);
					}
				}
			}
			px.y += b->aliasing;
		}
		px.x += b->aliasing;
	}
}

void		draw_lux(t_b *b)
{
	t_px		px;
	int			i;
	int			j;
	int			r;
	t_col		col;
	t_lux 		*lux;

	lux = b->lux;
	col = init_col(b->colmax, b->colmax, b->colmax);
	while (lux)
	{
		if (vect_dot(vect_sub(lux->ori, b->cam.pos), b->cam.dir) > 0)
		{
			px = pos2px(b, lux->ori);
			if (vect_norme(vect_sub(lux->ori, b->cam.pos)) / b->vp.dist < 1)
				r = 20;
			else
				r = 20 - (int)(0.4 * vect_norme(vect_sub(lux->ori, b->cam.pos)) / b->vp.dist);
			if (r < 1)
				r = 1;
			i = -r - 1;
			while (++i <= r)
			{
				j = -r - 1;
				while (++j <= r)
				{
					if (px.x + i >= 0 && px.y + j >= 0 && px.y + j < b->winy && px.x + i < b->winx &&
						(i * i) + (j * j) < r * r)
					{
						b->tab_px[px.y + j][px.x + i] = px;
						b->tab_px[px.y + j][px.x + i].col = col;
						b->tab_px[px.y + j][px.x + i].id = lux->id;
					}
				}
			}
		}
		lux = lux->next;
	}
}

int			main(int ac, char **av)
{
	t_b			b;

	if (main_help(ac, av))
		return (0);
	else if (ac == 2)
	{
		init_b(&b);
		init_win(&b);
		parse_main(&b, av[1]);
	}
	else if (ac < 2)
	{
		init_b(&b);
		init_win(&b);
		scene7(&b);
	}
	while (event(&b))
		rt(&b);
	SDL_DestroyWindow(b.win);
	SDL_Quit();
	return (0);
}
