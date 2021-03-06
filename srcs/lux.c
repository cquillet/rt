/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:58:32 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:36:09 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Add a lux to the list
*/

t_lux	*add_lux(t_b *b, t_lux lux)
{
	t_lux	*l;

	if (!b || b->nb_lux >= NB_OBJ_MAX)
		return (NULL);
	if (!(l = b->lux))
	{
		if (!(b->lux = (t_lux *)malloc(sizeof(t_lux))))
			error_quit(b, 3);
		l = b->lux;
	}
	else
	{
		while (l->next)
			l = l->next;
		l->next = (t_lux *)malloc(sizeof(t_lux));
		l = l->next;
	}
	if (l)
	{
		*l = lux;
		l->id = ++b->maxid;
		l->next = NULL;
		b->nb_lux++;
	}
	return (l);
}

/*
** Search a lux with the id
*/

t_lux	*search_lux(t_b *b, int id)
{
	t_lux	*l;

	if (id <= 0 || !b)
		return (NULL);
	l = b->lux;
	while (l && l->id != id)
		l = l->next;
	if (!l)
		return (NULL);
	return (l);
}
