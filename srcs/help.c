/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 18:56:35 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 16:32:38 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** To check the diferents help
*/

static int		man_help(void)
{
	ft_putendlcolor("./RTv1 usage         //How to use RTv1", YELLOW);
	ft_putendlcolor("./RTv1 help-parsing  //scene file example", YELLOW);
	return (1);
}

/*
** Help for file format
*/

int				help_parsing(void)
{
	ft_putendl("##NO TABULATIONS - ONLY SPACES ARE ALLOWED");
	ft_putendl("Caméra :       position");
	ft_putendl("EX : cam          0.0/0.0/10.0\n");
	ft_putendl("Lumière ambiante :       density");
	ft_putendl("EX : amb             0.4/0.4/0.4\n");
	ft_putendl("Plane :     a   b   c   d      color");
	ft_putendl("EX: plane  0.0 1.0 0.0 3.0  1.0/0.0/1.0\n");
	ft_putendl("Sphere :    Position       color     rayon");
	ft_putendl("EX: sph    3.0/0.0/5.0  1.0/0.0/1.0  1.0\n");
	ft_putendl("Cylindre :  Position       color          h       rayon");
	ft_putendl("EX : cyl   2.0/2.0/3.0  0.0/0.0/1.0  1.0/0.0/0.0  1.0\n");
	ft_putendl("Cone :      Position       color          h       angle");
	ft_putendl("EX : cone  0.0/0.0/5.0  1.0/1.0/1.0  1.0/0.0/0.0  20.0\n");
	ft_putendl("Lumiere :   Position       Diffuse    Spéculaire");
	ft_putendl("EX : lux   0.0/0.0/5.0  0.0/0.2/0.2  0.0/0.5/0.5\n");
	ft_putendl("----------------------------------------------------------\n");
	ft_putendl("File exemple :\n");
	ft_putendl("amb      0.4/0.4/0.4");
	ft_putendl("plane    0.0 1.0 0.0 3.0  1.0/0.0/1.0");
	ft_putendl("sph      3.0/0.0/5.0      1.0/0.0/1.0     0.2");
	ft_putendl("cyl      2.0/2.0/3.0      0.0/0.0/1.0     1.0/0.0/0.0    1.0");
	ft_putendl("cone     0.0/0.0/5.0      1.0/1.0/1.0     1.0/0.0/0.0    20.0");
	ft_putendl("lux      0.0/0.0/5.0      0.0/0.2/0.2     0.0/0.5/0.5");
	ft_putendl("lux      2.0/3.0/5.0      0.7/0.7/0.7     0.7/0.7/0.7");
	return (1);
}

static int		usage(void)
{
	ft_putendlcolor("./RTv1               //Start with the basic map.", GREEN);
	ft_putendlcolor("     OR", GREEN);
	ft_putendlcolor("./RTv1 scene_file    //Start with the given file.", GREEN);
	ft_putendlcolor("     OR", GREEN);
	ft_putendlcolor("./RTv1 help          //For more infos", GREEN);
	return (1);
}

int				main_help(int ac, char **av)
{
	char		*txt;

	if (ac > 2 || !av)
		return (man_help());
	else if (ac == 2)
	{
		txt = av[1];
		if (!ft_strcmp(txt, "help"))
			return (man_help());
		else if (!ft_strcmp(txt, "help-parsing"))
			return (help_parsing());
		else if (!ft_strcmp(txt, "usage"))
			return (usage());
	}
	return (0);
}
