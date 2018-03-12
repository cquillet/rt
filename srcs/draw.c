/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 05:00:18 by cquillet          #+#    #+#             */
/*   Updated: 2018/03/12 05:42:35 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	draw_aliasing(t_b *b, t_px px)
{
	int				i;
	int				j;
	unsigned int	c;

	c = col2int(gamma_corr(color_multnb(px.col, 1 / b->colmax), 1.0, b->gamma));
	i = -1;
	while (++i < b->aliasing)
	{
		j = -1;
		while (++j < b->aliasing)
		{
			if (px.y + j < b->winy && px.x + i < b->winx)
			{
				SDL_LockSurface(b->img);
				*((unsigned int *)b->img->pixels +
										b->winx * (px.y + j) + px.x + i) = c;
				SDL_UnlockSurface(b->img);
			}
		}
	}
}

void		draw(t_b *b)
{
	int			x;
	int			y;

	x = 0;
	while (x < b->winx)
	{
		y = 0;
		while (y < b->winy)
		{
			draw_aliasing(b, b->tab_px[y][x]);
			y += b->aliasing;
		}
		x += b->aliasing;
	}
}

static void	draw_lux_aliasing(t_b *b, t_px px, int r)
{
	int			i;
	int			j;

	i = -r - 1;
	while (++i <= r)
	{
		j = -r - 1;
		while (++j <= r)
		{
			if (px.x + i >= 0 && px.y + j >= 0 &&
									px.y + j < b->winy && px.x + i < b->winx &&
									(i * i) + (j * j) < r * r)
			{
				b->tab_px[px.y + j][px.x + i] = px;
			}
		}
	}
}

void		draw_lux(t_b *b)
{
	t_px		px;
	int			r;
	t_lux		*lux;

	lux = b->lux;
	while (lux)
	{
		if (vect_dot(vect_sub(lux->ori, b->cam.pos), b->cam.dir) > 0)
		{
			px = pos2px(b, lux->ori);
			r = 20;
			if (vect_norme(vect_sub(lux->ori, b->cam.pos)) / b->vp.dist < 1)
				px.col = init_col(b->colmax, 0., 0.);
			else
			{
				px.col = init_col(b->colmax, b->colmax, b->colmax);
				r = r - (int)(0.4 * vect_norme(vect_sub(lux->ori, b->cam.pos)) / b->vp.dist);
			}
			if (r < 1)
			{
				px.col = init_col(0., 0., b->colmax);
				r = 1;
			}
			px.id = lux->id;
			draw_lux_aliasing(b, px, r);
		}
		lux = lux->next;
	}
}
