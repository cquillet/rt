/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:17:12 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/06 15:08:14 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*
** Catch and throw the events
*/

int		event(t_b *b)
{
	SDL_Event	event;
	int			ev;

	while (SDL_PollEvent(&event))
	{
		ev = event.key.keysym.sym;
		if (event.type == SDL_QUIT || ev == SDLK_ESCAPE)
			return (0);
		else if (ev == SDLK_3 || ev == SDLK_4)
			ev_qualitat(b, ev);
		else if (ev == SDLK_COMMA || ev == SDLK_PERIOD)
			ev_gamma(b, ev);
		else if (ev == SDLK_r)
			ev_reset(b);
		else if (event.type == SDL_MOUSEBUTTONDOWN
			&& event.button.button == SDL_BUTTON_LEFT)
			ev_mouse(b);
		else if (ev == SDLK_SPACE)
			b->act->action *= -1;
		else
			event_move(b, ev);
	}
	return (1);
}

/*
** Return to basic values
*/

void	ev_reset(t_b *b)
{
	init_cam(b);
	b->lux->ori = init_vect(0.0, 0.0, 25.0);
	b->aliasing = 4;
}

/*
** Event to change the qualitat
*/

void	ev_qualitat(t_b *b, int ev)
{
	if (ev == SDLK_3 && b->aliasing > 1)
		b->aliasing -= 1;
	else if (ev == SDLK_4 && b->aliasing <= b->winy / 4
			&& b->aliasing <= b->winx / 4)
		b->aliasing += 1;
}

/*
** Event to change the gamma
*/

void	ev_gamma(t_b *b, int ev)
{
	if (ev == SDLK_COMMA && b->gamma > 0.1)
		b->gamma -= 0.1;
	else if (ev == SDLK_PERIOD && b->gamma < 2.0)
		b->gamma += 0.1;
}
