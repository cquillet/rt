/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:23:12 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 15:39:56 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Clean and end the program
*/

void	clean_b(t_b *b)
{
	if (b)
	{
		clean_obj(b->obj);
		clean_lux(b->lux);
		clean_act(b->act);
		SDL_DestroyWindow(b->win);
	}
	SDL_Quit();
}

void	clean_obj(t_obj *obj)
{
	t_obj	*tmp;
	t_obj	*tmp2;

	if (obj)
	{
		tmp = obj;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}

void	clean_lux(t_lux *lux)
{
	t_lux	*tmp;
	t_lux	*tmp2;

	if (lux)
	{
		tmp = lux;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}

void	clean_act(t_act *act)
{
	t_act	*tmp;
	t_act	*tmp2;

	if (act)
	{
		tmp = act;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}

void	clean_vl(t_vl *vl)
{
	t_vl	*tmp;
	t_vl	*tmp2;

	if (vl)
	{
		tmp = vl;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
}
