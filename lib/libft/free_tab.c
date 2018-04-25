/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 15:30:43 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 15:27:54 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Free a tab
*/

void	free_tab(void **tab)
{
	char	**tmp;
	char	**s;

	if (tab && *tab)
	{
		tmp = (char **)tab;
		while (*tmp)
		{
			s = tmp + 1;
			if (tmp)
				ft_strdel(tmp);
			tmp = s;
		}
		free(tab);
		tab = NULL;
	}
}
