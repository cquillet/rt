/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 20:43:18 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 11:03:37 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Refresh the dir vector
*/

void	refresh_dir(t_cam *cam, t_v v)
{
	cam->dir = v;
	cam->dirright = vect_prod(v, cam->dirup);
}

/*
** Refresh the dirrup vector
*/

void	refresh_dirup(t_cam *cam, t_v v)
{
	cam->dirup = v;
	cam->dir = vect_prod(v, cam->dirright);
}

/*
** Refresh the dirright vector
*/

void	refresh_dirright(t_cam *cam, t_v v)
{
	cam->dirright = v;
	cam->dirup = vect_prod(v, cam->dir);
}
