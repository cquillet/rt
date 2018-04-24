/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:44:31 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/24 21:19:36 by cquillet         ###   ########.fr       */
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
	if (ev == SDLK_x)
		ev_screenshot(b);
	else if (ev == SDLK_z)
		b->rec = !b->rec;
	else if (ev == SDLK_h)
		b->draw_lights = !b->draw_lights;
}

/*
** Take a screenshot and save it with current date and time
** bmp to jpg : find . -type f -name '*.bmp' -exec convert {} {}.jpg \;
*/

void	ev_screenshot(t_b *b)
{
	SDL_Renderer	*renderer;
	SDL_Surface		*screen;
	char			*name;
	char			*tmp;

	name = ft_strdup("screenshots/Screenshot");
	ft_strjoin_free(name, (tmp = ft_itoa(time(NULL))));
	ft_strdel(&tmp);
	ft_strjoin_free(name, ".bmp");
	renderer = SDL_GetRenderer(b->win);
	screen = SDL_CreateRGBSurface(0, b->winx, b->winy,
						32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
											screen->pixels, screen->pitch);
	SDL_SaveBMP(screen, name);
	ft_strdel(&name);
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
}
