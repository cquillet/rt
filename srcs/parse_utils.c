/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:49:19 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/08 17:35:28 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Check and convert a string to a vector
*/

t_v			parse_vect(char *s)
{
	t_v		v;
	int		i[2];
	int		p;
	char	**tab;

	tab = ft_strsplit(s, '/');
	i[0] = -1;
	while (tab[++i[0]])
	{
		i[1] = -1;
		p = 0;
		while (tab[i[0]][++i[1]])
		{
			if (ft_isdigit(tab[i[0]][i[1]]) || (tab[i[0]][i[1]] == '.' && !p))
			{
				if (tab[i[0]][i[1]] == '.')
					p = 1;
			}
			else
				parse_err(2, s);
		}
	}
	v = init_vect(ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2]));
	free_tab((void **)tab);
	return (v);
}

/*
** Check and convert a string to a vector
*/

t_col		parse_col(char *s)
{
	t_col	col;
	int		i[2];
	int		p;
	char	**tab;

	tab = ft_strsplit(s, '/');
	i[0] = -1;
	while (tab[++i[0]])
	{
		i[1] = -1;
		p = 0;
		while (tab[i[0]][++i[1]])
		{
			if (ft_isdigit(tab[i[0]][i[1]]) || (tab[i[0]][i[1]] == '.' && !p))
			{
				if (tab[i[0]][i[1]] == '.')
					p = 1;
			}
			else
				parse_err(2, s);
		}
	}
	col = init_col(ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2]));
	free_tab((void **)tab);
	return (col);
}

/*
** Check if a str is a correct double then atof() it
*/

double		parse_double(char *s)
{
	int		i;
	int		p;

	p = 0;
	i = -1;
	while (s[++i])
	{
		if (ft_isdigit(s[i]) || (s[i] == '.' && p == 0))
		{
			if (s[i] == '.')
				p = 1;
		}
		else
			parse_err(1, s);
	}
	return (ft_atof(s));
}
