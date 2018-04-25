/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel2dim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:46:44 by cquillet          #+#    #+#             */
/*   Updated: 2018/04/23 19:36:19 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>
int		ft_memdel2dim(void ***t1, size_t n)
{
//	char	**t;
	char	***t;

//	t = (char **)(*t1);
	t = (char ***)t1;
	if (*t)
	{
		printf ("t %p\n", *t);
		n = 0;
		while ((*t)[n])
		{
			printf ("n=%zu %p\n", n, (*t)[n]);
			n++;
		}
		while (n--)
		{
		//	free((*t)[n]);
		//	(*t)[n] = NULL;
			ft_strdel(&(*t)[n]);
		}
		free(*t);
		*t = NULL;
	}
	return (0);
}
