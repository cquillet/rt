/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:23:12 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/24 22:30:38 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Clean and end the program
*/

void	clean_b(t_b *b)
{
/*	char *w;
	w = (char *)b;
	printf("file %p -> %p\n", w, b + 200);
	while ((unsigned int)w < (unsigned int)(b + 200))
		dprintf (2, "w %p / %p\n", w++, b + 200);*/
	clean_obj(b->obj);
	clean_lux(b->lux);
	clean_act(b->act);
	clean_vl(b->vl);
	ft_strdel(&b->av);
//	SDL_FreeSurface(b->img);
	SDL_DestroyWindow(b->win);
	SDL_Quit();
	// free_tab(b->tab_px);
		while (1);
}

void	clean_obj(t_obj *obj)
{
	t_obj	*tmp;
	t_obj	*tmp2;

	if (obj)
	{
		printf("obj %p\n", obj);
		tmp = obj;
		printf("tmp %p\n", tmp);
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
