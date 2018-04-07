/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:16:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/03 17:10:42 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** To animate the scene we need to
** init_act();
** set_act();
** action();
*/

void		action(t_act *act)
{
	if (act->action < 0)
		return ;
	while (act)
	{
		if (act->action == 1)
			;
		else if (act->action == 2)
			act_movaxis(act);
		else if (act->action == 3)
			act_color(act->obj1);
		act = act->next;
	}
}

/*
** Add an action to the list
*/

t_act		*add_action(t_b *b, t_act act)
{
	t_act	*l;

	if (!b)
		return (NULL);
	if (!(l = b->act))
	{
		b->act = (t_act *)malloc(sizeof(t_act));
		*(b->act) = act;
		b->act->next = NULL;
		return (b->act);
	}
	while (l->next)
		l = l->next;
	l->next = (t_act *)malloc(sizeof(t_act));
	l = l->next;
	*l = act;
	l->next = NULL;
	return (l);
}

/*
** Move inline of the axe defined and between min and max
*/

void		act_movaxis(t_act *act)
{
	double tmp;

	if (act->min >= act->max)
	{
		tmp = act->min;
		act->min = act->max;
		act->max = tmp;
	}
	if (*act->axis >= act->max)
		act->p = 0;
	else if (*act->axis <= act->min)
		act->p = 1;
	if (act->p == 1)
		*act->axis += act->speed;
	else
		*act->axis -= act->speed;
}

/*
** To change the color
*/

void		act_color(t_obj *obj)
{
	obj->tex.col.r = (double)rand() / (double)RAND_MAX;
	obj->tex.col.g = (double)rand() / (double)RAND_MAX;
	obj->tex.col.b = (double)rand() / (double)RAND_MAX;
}
