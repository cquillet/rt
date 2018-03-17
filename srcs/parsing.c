/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:03:34 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 17:38:58 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Start the parsing
*/

void	parse_main(t_b *b, char *av)
{
	int		fd;
	char	*s;

	if (!ft_strcmp(av, "help"))
		help_parsing();
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_err(3, av);
	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		s = ft_strtrim(s);
		if (s[0] != '#' && (s[0] != '/' && s[1] != '/'))
			parse_zob(b, s);
		ft_strdel(&s);
	}
	close(fd);
}

/*
** Pour parser des zobs
*/

void	parse_zob(t_b *b, char *av)
{
	char **tab;

	tab = ft_strsplit(av, ' ');
	if (!ft_strcmp(tab[0], "plane"))
		add_obj(b, init_plane(parse_double(tab[1]), parse_double(tab[2]),
		 parse_double(tab[3]), parse_double(tab[4]), parse_col(tab[5])));
	else if (!ft_strcmp(tab[0], "sph"))
		add_obj(b, init_sph(parse_vect(tab[1]), parse_col(tab[2]), 1.0));
	else if (!ft_strcmp(tab[0], "cyl"))
		add_obj(b, init_cyl(parse_vect(tab[1]), parse_col(tab[2]),
		 parse_vect(tab[3]), parse_double(tab[4])));
	else if (!ft_strcmp(tab[0], "cone"))
		add_obj(b, init_cone(parse_vect(tab[1]), parse_col(tab[2]),
		 parse_vect(tab[3]), parse_double(tab[4])));
	else if (!ft_strcmp(tab[0], "lux"))
		add_lux(b, init_lux(parse_vect(tab[1]), parse_col(tab[2]),
		 parse_col(tab[3])));
	else if (!ft_strcmp(tab[0], "amb"))
		b->amb = parse_col(tab[1]);
	else
		parse_err(0, "");
	free_tab((void **)tab);
}
