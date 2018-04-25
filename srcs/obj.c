/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:02:11 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:35:58 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	Add an obj to the list
*/

t_obj	*add_obj(t_b *b, t_obj obj)
{
	t_obj	*l;

	if (!b || b->nb_obj >= NB_OBJ_MAX)
		return (NULL);
	if (!(l = b->obj))
	{
		if (!(b->obj = (t_obj *)malloc(sizeof(t_obj))))
			error_quit(b, 3);
		l = b->obj;
	}
	else
	{
		while (l->next)
			l = l->next;
		l->next = (t_obj *)malloc(sizeof(t_obj));
		l = l->next;
	}
	if (l)
	{
		*l = obj;
		l->id = ++b->maxid;
		l->next = NULL;
		b->nb_obj++;
	}
	return (l);
}

/*
** Search an obj in the list
*/

t_obj	*search_obj(t_b *b, int id)
{
	t_obj	*l;

	if (id <= 0 || !b)
		return (NULL);
	l = b->obj;
	while (l && l->id != id)
		l = l->next;
	if (!l)
		return (NULL);
	return (l);
}

/*
** To delete a selected object
*/

void	delete_obj(t_b *b, int id)
{
	t_obj	*l;
	t_obj	*obj;

	if (!b || !b->obj || id < 0 || b->nb_obj < 2)
		return ;
	l = b->obj;
	if (b->obj->id == id)
	{
		b->obj = l->next;
		free(l);
		b->nb_obj--;
		return ;
	}
	while (l && l->next)
	{
		if (l->next->id == id)
		{
			obj = l->next->next;
			free(l->next);
			l->next = obj;
			b->nb_obj--;
			return ;
		}
		l = l->next;
	}
}
