/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:56:39 by vmercadi          #+#    #+#             */
/*   Updated: 2017/12/13 22:00:14 by vmercadi         ###   ########.fr       */
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
}
