/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 18:54:51 by cquillet          #+#    #+#             */
/*   Updated: 2018/03/12 09:47:51 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "RTv1.h"

int			barely_zero(double a)
{
	return (((a < 0.) ? -a : a) < MARGIN_FLOAT);
}

int			barely_equals(double a, double b)
{
	return (barely_zero(a - b));
}

int		scale(int value, int min_max[2], int new_min_max[2])
{
	int		min;
	int		max;
	int		new_min;
	int		new_max;

	max = min_max[1];
	new_max = new_min_max[1];
	if (value == max)
		return (new_max);
	min = min_max[0];
	new_min = new_min_max[0];
	if (value == min)
		return (new_min);
	if (!(max - min))
		return (0);
	return ((value - min) * (new_max - new_min) / (max - min) + new_min);
}

double	scalef(double value, double min_max[2], double new_min_max[2])
{
	double	min;
	double	max;
	double	new_min;
	double	new_max;

	max = min_max[1];
	new_max = new_min_max[1];
	if (barely_equals(value, max))
		return (new_max);
	min = min_max[0];
	new_min = new_min_max[0];
	if (barely_equals(value, min))
		return (new_min);
	if (barely_zero(max - min))
		return (0.);
	return ((value - min) / (max - min) * (new_max - new_min) + new_min);
}

unsigned int	spectrum_color(int value, int min, int max)
{
	int		c;

	c = scale(value, (int [2]){min, max}, (int [2]){0, 0x5F9});
	if (c < 0xFF)
		return (0xFF00FE - c);
	if (c < 0x1FE)
		return (0xFF0100 + ((c - 0xFF) << 8));
	if (c < 0x2FD)
		return (0xFEFF00 - ((c - 0x1FE) << 16));
	if (c < 0x3FC)
		return (0x00FF01 + (c - 0x2FD));
	if (c < 0x4FB)
		return (0x00FEFF - ((c - 0x3FC) << 8));
	return (0x0100FF + ((c - 0x4FB) << 16));
}

unsigned int	spectrum_gray(int value, int min, int max)
{
	int		c;

	c = scale(value, (int [2]){min, max}, (int [2]){0, 0xFF});
	return ((c << 16) | (c << 8) | c);
}

unsigned int	rgb_between(int value, int start_end[2],
							unsigned int color_start, unsigned int color_end)
{
	unsigned int	c;
	int				start;
	int				end;

	start = start_end[0];
	end = start_end[1];
	c = (scale(value, start_end,
		(int [2]){(color_start >> 16) & 0xFF, (color_end >> 16) & 0xFF}) << 16);
	c |= (scale(value, start_end,
		(int [2]){(color_start >> 8) & 0xFF, (color_end >> 8) & 0xFF}) << 8);
	c |= (scale(value, start_end,
		(int [2]){color_start & 0xFF, color_end & 0xFF}));
	return (c);
}

unsigned int	spectrum_colorf(double value, double min, double max)
{
	int			c;

	c = (int)scalef(value, (double [2]){min, max}, (double [2]){0, 0x5F9});
	if (c < 0xFF)
		return (0xFF00FE - c);
	if (c < 0x1FE)
		return (0xFF0100 + ((c - 0xFF) << 8));
	if (c < 0x2FD)
		return (0xFEFF00 - ((c - 0x1FE) << 16));
	if (c < 0x3FC)
		return (0x00FF01 + (c - 0x2FD));
	if (c < 0x4FB)
		return (0x00FEFF - ((c - 0x3FC) << 8));
	return (0x0100FF + ((c - 0x4FB) << 16));
}

unsigned int	spectrum_grayf(double value, double min, double max)
{
	int			c;

	c = (int)scalef(value, (double [2]){min, max}, (double [2]){0., 255.});
	return ((c << 16) | (c << 8) | c);
}

unsigned int	rgb_betweenf(double value, double start_end[2],
							unsigned int color_start, unsigned int color_end)
{
	unsigned int	c;
	double			start;
	double			end;

	start = start_end[0];
	end = start_end[1];
	c = ((unsigned int)scalef(value, start_end,
		(double [2]){(color_start >> 16) & 0xFF, (color_end >> 16) & 0xFF})
		<< 16);
	c |= ((unsigned int)scalef(value, start_end,
		(double [2]){(color_start >> 8) & 0xFF, (color_end >> 8) & 0xFF})
		<< 8);
	c |= ((unsigned int)scalef(value, start_end,
		(double [2]){color_start & 0xFF, color_end & 0xFF}));
	return (c);
}
/*
int main(int ac, char **av)
{
	int i = 0;

	while (i < 100)
	{
		printf("%d/100 -> %x\n", i, spectrum_color(i, 0, 100));
		i++;
	}
	return 0;
}*/
