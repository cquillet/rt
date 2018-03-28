/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 05:00:18 by cquillet          #+#    #+#             */
/*   Updated: 2018/03/20 16:29:17 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	draw_aliasing(t_b *b, int x, int y)
{
	int				i;
	int				j;
	unsigned int	c;
	t_px			px;

	i = -1;
	while (++i < b->aliasing)
	{
		j = -1;
		while (++j < b->aliasing)
		{
			if (y + j < b->winy && x + i < b->winx)
			{
				px = b->tab_px[y + j][x + i];
				c = col2int(gamma_corr(color_multnb(px.col, 1.0 / b->colmax),
																1.0, b->gamma));
				SDL_LockSurface(b->img);
				*((unsigned int *)b->img->pixels +
										b->winx * (y + j) + x + i) = c;
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
			draw_aliasing(b, x, y);
			y += b->aliasing;
		}
		x += b->aliasing;
	}
}

static void	draw_lux_circle(t_b *b, t_px center, int r)
{
	int			i;
	int			j;
	t_px		px;

	px = center;
	i = -r - 1;
	while (++i <= r)
	{
		j = -r - 1;
		while (++j <= r)
		{
			px.x = center.x + i;
			px.y = center.y + j;
			if (px.x >= 0 && px.y >= 0 && px.y < b->winy && px.x < b->winx &&
													(i * i) + (j * j) < r * r)
			{
				b->tab_px[px.y][px.x] = px;
			}
		}
	}
}

void		draw_lux(t_b *b)
{
	t_px		px;
	int			r;
	t_lux		*lux;
	t_v			v;

	lux = b->lux;
	while (lux)
	{
		if (vect_dot((v = vect_sub(lux->ori, b->cam.pos)), b->cam.dir) > 0)
		{
			px = pos2px(b, lux->ori);
			px.col = init_col(b->colmax, b->colmax, b->colmax);
			r = 20 - (int)(0.4 * vect_norme(v) / b->vp.dist);
			r = (r < 1) ? 1 : r;
			r = (r > 20) ? 20 : r;
			if (r == 20)
				px.col = init_col(b->colmax, 0., 0.);
			if (r == 1)
				px.col = init_col(0., 0., b->colmax);
			px.id = lux->id;
			draw_lux_circle(b, px, r);
		}
		lux = lux->next;
	}
}
