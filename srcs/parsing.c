/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:03:34 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:45:26 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Start the parsing get the values from the file
*/

void		parse_main(t_b *b, char *av)
{
	int		fd;
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_err(b, 3, av);
	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		i++;
		tmp = ft_strtrim(s);
		ft_strdel(&s);
		s = tmp;
		if (s && s[0] && s[0] != '#' && s[0] != '/' && s[1] && s[1] != '/'
														&& ft_strlen(s) > 1)
			parse_zob(b, s);
		ft_strdel(&s);
	}
	ft_strdel(&s);
	close(fd);
	if (!i)
		parse_err(b, 3, av);
}

/*
** Pour parser des zobs
*/

static int	parse_values(t_b *b, char **tab, size_t n)
{
	t_obj	*obj;

	obj = NULL;
	if (n == 6 && !ft_strcmp(tab[0], "plane"))
		obj = add_obj(b, init_plane(init_vect(
			parse_double(b, tab[1]), parse_double(b, tab[2]),
	parse_double(b, tab[3])), parse_double(b, tab[4]), parse_col(b, tab[5])));
	else if (n == 4 && !ft_strcmp(tab[0], "sph"))
		obj = add_obj(b, init_sph(parse_vect(b, tab[1]), parse_col(b, tab[2]),
			parse_double(b, tab[3])));
	else if (n == 5 && !ft_strcmp(tab[0], "cyl"))
		obj = add_obj(b, init_cyl(parse_vect(b, tab[1]), parse_col(b, tab[2]),
						parse_vect(b, tab[3]), parse_double(b, tab[4])));
	else if (n == 5 && !ft_strcmp(tab[0], "cone"))
		obj = add_obj(b, init_cone(parse_vect(b, tab[1]), parse_col(b, tab[2]),
						parse_vect(b, tab[3]), parse_double(b, tab[4])));
	else
		return (-1);
	return (obj ? obj->form : -1);
}

void		parse_zob(t_b *b, char *av)
{
	char	**tab;
	size_t	n;
	int		r;

	if (!(tab = ft_strsplit(av, ' ')))
		return ;
	r = 0;
	n = 0;
	while (tab[n])
		n++;
	if (n == 2 && (!ft_strcmp(tab[0], "cam")))
		b->cam.pos = parse_vect(b, tab[1]);
	else if (n == 2 && !ft_strcmp(tab[0], "amb"))
		b->amb = parse_col(b, tab[1]);
	else if (n == 4 && !ft_strcmp(tab[0], "lux"))
	{
		if (b->nb_lux < NB_OBJ_MAX)
			add_lux(b, init_lux(parse_vect(b, tab[1]), parse_col(b, tab[2]),
														parse_col(b, tab[3])));
	}
	else if (b->nb_obj < NB_OBJ_MAX)
		r = parse_values(b, tab, n);
	free_tab((void **)tab);
	if (r < 0)
		parse_err(b, 0, av);
}
