/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:56:39 by vmercadi          #+#    #+#             */
/*   Updated: 2018/01/30 22:19:18 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	error()
{

}

void	error_quit(int e)
{
	if (e == 1)
		ft_putendl_fd("FAILED to init SDL" ,2);
	else if (e == 2)
		ft_putendl("FAILED to open file");
	exit (e);
}
