/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:56:39 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/03 17:23:42 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error_quit(int e)
{
	if (e == 1)
		ft_putendl_fd("FAILED to init SDL", 2);
	else if (e == 2)
		ft_putendl("FAILED to open file");
	exit(e);
}

/*
** Errors happened while parsing
*/

void	parse_err(int e, char *s)
{
	if (e == 0)
		ft_putstrcolor("Error in obj name : ", RED);
	else if (e == 1)
		ft_putstrcolor("Some double is not well formated : ", RED);
	else if (e == 2)
		ft_putstrcolor("Some vector is not well formated : ", RED);
	else if (e == 3)
		ft_putstrcolor("The file given is not a scene : ", RED);
	else if (e == 0 && ft_strchr(s, '\t'))
		ft_putstrcolor("The file given is not a scene : ", RED);
	ft_putendl(s);
	exit(1);
}
