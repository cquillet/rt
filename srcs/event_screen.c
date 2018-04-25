/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:44:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/25 18:42:59 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Dans After effect : File->import->import multiple files | ET BIM une vidéo.
*/

void	ev_screen(t_b *b, SDL_Event event)
{
	int		ev;

	ev = event.key.keysym.sym;
	if (ev == SDLK_h && event.key.state == SDL_RELEASED)
		b->draw_lights = !b->draw_lights;
}
