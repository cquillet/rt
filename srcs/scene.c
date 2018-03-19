/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:22:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/03/19 19:39:01 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	scene1(t_b *b)
{
	add_lux(b, init_lux(init_vect(5.0, -5.0, -15.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	b->lux->dif = init_col(0.0, 0.0, 0.8);
	b->lux->spe = init_col(0.0, 0.0, 0.8);

	add_lux(b, init_lux(init_vect(-5.0, 5.0, -5.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	b->lux->next->dif = init_col(1.0, 0.0, 1.0);
	b->lux->next->spe = init_col(0.5, 0.0, 0.5);

	add_lux(b, init_lux(init_vect(0.0, 0.0, -5.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	b->lux->next->next->dif = init_col(1.0, 1.0, 0.0);
	b->lux->next->next->spe = init_col(0.5, 0.5, 0.0);

	add_lux(b, init_lux(init_vect(0.0, 0.0, 5.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	b->lux->next->next->dif = init_col(0.0, 1.0, 0.0);
	b->lux->next->next->spe = init_col(0.0, 1.0, 0.0);

	add_obj(b, init_sph(init_vect(2, 0, 5), init_col(0.6, 0.2, 0.2), 1.0));
	add_obj(b, init_sph(init_vect(-2, 2, 5), init_col(1.0, 1.0, 1.0), 1.0));
	add_obj(b, init_sph(init_vect(0, -2, 5), init_col(1.0, 1.0, 0.0), 1.0));
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.0, init_col(0.1, 0.0, 0.0)));
	add_action(b, init_act(b->obj, 2, 3));
	b->act->speed *= 10;
	b->act->max = 10;
	b->act->min = -10;
	// add_action(b, init_act(b->obj->next, 3, 1));
	add_action(b, init_act(b->obj->next, 2, 1));
	add_action(b, init_act(b->obj->next, 2, 2));
	add_action(b, init_act(b->obj->next, 2, 3));
	add_action(b, init_act(b->obj->next->next, 2, 1));
}

void	scene2(t_b *b)
{
	t_obj	*obj;

	add_lux(b, init_lux(init_vect(-1.0, -1.0, 4.0), init_col(0.7, 0.7, 0.7), init_col(0.7, 0.7, 0.7)));
	add_lux(b, init_lux(init_vect(2.0, -2.0, 5.0), init_col(0.7, 0.7, 0.7), init_col(0.7, 0.7, 0.7)));
	// b->lux->next->dif = init_col(0.0, 0.0, 1.0);
	add_obj(b, init_sph(init_vect(0, 0, 7), init_col(COL_YELLOWGREEN), 1.0));

//	obj = add_obj(b, init_cyl(init_vect(0, 2, 4), init_col(COL_GREY), init_vect(3.0, 1.0, 1.0), 1.3));
	obj = add_obj(b, init_cone(init_vect(0, 2, 4), init_col(COL_GREY), init_vect(3.0, 1.0, 1.0), 20.));
	obj->tex.kd = init_col(0.5, 0.5, 0.5);
	obj->tex.ks = init_col(1., 1., 1.);
//	obj->tex.rug = 3.;
	//Mur fond
	add_obj(b, init_plane(init_vect(0.0, 0.0, 1.0), -10.0, init_col(1.0, 0.0, 1.0)));
	//Mur droite
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), -3.0, init_col(1.0, 0.0, 0.0)));
	//Mur gauche
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.0, init_col(0.0, 1.0, 0.0)));
	//Plafond
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), -3.0, init_col(0.0, 0.0, 1.0)));
	//sol
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 3.0, init_col(0.5, 0.5, 0.5)));
	b->amb = init_col(1.0, 1.0, 1.0);
}

void	scene3(t_b *b)
{
	add_lux(b, init_lux(init_vect(0.0, 0.0, -25.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	add_obj(b, init_sph(init_vect(0, 0, 10), init_col(1.0, 1.0, 1.0), 1.0));
	b->obj->tex.ks = init_col(0.0, 0.0, 0.0);
	b->obj->tex.kd = init_col(1.0, 1.0, 1.0);

	add_obj(b, init_sph(init_vect(2, 2, 10), init_col(0.0, 0.0, 1.0), 1.0));
	b->obj->next->tex.ks = init_col(1.0, 1.0, 1.0);
	b->obj->next->tex.kd = init_col(0.0, 0.0, 0.0);

	add_obj(b, init_sph(init_vect(0, 2, 10), init_col(1.0, 1.0, 0.0), 1.0));
	add_obj(b, init_sph(init_vect(2, 0, 10), init_col(1.0, 0.0, 0.0), 1.0));
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.0, init_col(1.0, 0.0, 0.0)));
}

void	scene4(t_b *b)
{
	add_lux(b, init_lux(init_vect(0.0, 1.0, 2.0), init_col(0.7, 0.7, 0.7), init_col(0.3, 0.3, 0.3)));
	add_obj(b, init_sph(init_vect(0, 0, 5), init_col(1.0, 0.0, 0.0), 1.0));
}

void	scene5(t_b *b)
{
	t_obj	*obj;
	t_act	*act;
	// t_lux	*lux;

	b->cam.pos = init_vect(0.0, 0.0, -10);

	add_lux(b, init_lux(init_vect(0.0, 3.0, -11.0), init_col(COL_YELLOWGREEN), init_col(COL_YELLOWGREEN)));
	add_lux(b, init_lux(init_vect(3.0, 1.0, -9.0), init_col(COL_BURLYWOOD), init_col(COL_BURLYWOOD)));
	add_lux(b, init_lux(init_vect(3.0, 3.0, -6.0), init_col(COL_DARKTURQUOISE), init_col(COL_DARKTURQUOISE)));
	add_lux(b, init_lux(init_vect(-3.0, -3.0, -3.0), init_col(COL_CORNFLOWERBLUE), init_col(COL_CORNFLOWERBLUE)));
	add_lux(b, init_lux(init_vect(1.0, 1.0, -15.0), init_col(COL_MISTYROSE), init_col(COL_MISTYROSE)));
	add_lux(b, init_lux(init_vect(-1.0, -1.0, 0.0), init_col(COL_NAVAJOWHITE), init_col(COL_NAVAJOWHITE)));
	add_lux(b, init_lux(init_vect(1.0, 0.0, 11.0), init_col(COL_LEMONCHIFFON), init_col(COL_LEMONCHIFFON)));
	add_lux(b, init_lux(init_vect(0.0, 1.0, 9.0), init_col(COL_MEDIUMAQUAMARINE), init_col(COL_MEDIUMAQUAMARINE)));
	add_lux(b, init_lux(init_vect(0.0, -1.0, 6.0), init_col(COL_LIGHTGOLDENRODYELLOW), init_col(COL_LIGHTGOLDENRODYELLOW)));
	add_lux(b, init_lux(init_vect(-3.0, -3.0, 3.0), init_col(COL_TOMATO), init_col(COL_TOMATO)));

	// add_lux(b, init_lux(init_vect(0.0, 3.0, -11.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(3.0, 1.0, -9.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(3.0, 3.0, -6.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(-3.0, -3.0, -3.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(1.0, 1.0, -15.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(-1.0, -1.0, 0.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(1.0, 0.0, 11.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(0.0, 1.0, 9.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(0.0, -1.0, 6.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	// add_lux(b, init_lux(init_vect(-3.0, -3.0, 3.0), init_col(COL_WHITE), init_col(COL_WHITE)));
	//gauche
	add_obj(b, init_sph(init_vect(3.0, 0.0, 10), init_col(COL_CYAN), 1.0));
	obj = b->obj;
	obj->r = 0.8;
	add_action(b, init_act(obj, 2, 3));
	act = b->act;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//centre
	add_obj(b, init_sph(init_vect(0.0, 0.0, 5), init_col(COL_WHITE), 1.0));
	obj = obj->next;
	obj->r = 1.5;

	//droite
	add_obj(b, init_sph(init_vect(-3.0, 0.0, 10), init_col(COL_CYAN), 1.0));
	obj = obj->next;
	obj->r = 0.8;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//haut
	add_obj(b, init_sph(init_vect(0.0, 3.0, 10), init_col(COL_CYAN), 1.0));
	obj = obj->next;
	obj->r = 0.8;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;


	//bas
	add_obj(b, init_sph(init_vect(0.0, -3.0, 10), init_col(COL_CYAN), 1.0));
	obj = obj->next;
	obj->r = 0.8;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//Haut-gauche
	add_obj(b, init_sph(init_vect(1.5, 1.5, -10), init_col(COL_DEEPPINK), 1.0));
	obj = obj->next;
	obj->r = 0.5;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//Bas-droite
	add_obj(b, init_sph(init_vect(-1.5, -1.5, -10), init_col(COL_DEEPPINK), 1.0));
	obj = obj->next;
	obj->r = 0.5;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//Haut-droite
	add_obj(b, init_sph(init_vect(-1.5, 1.5, -10), init_col(COL_DEEPPINK), 1.0));
	obj = obj->next;
	obj->r = 0.5;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;

	//Bas-gauche
	add_obj(b, init_sph(init_vect(1.5, -1.5, -10), init_col(COL_DEEPPINK), 1.0));
	obj = obj->next;
	obj->r = 0.5;
	add_action(b, init_act(obj, 2, 3));
	act = act->next;
	// act->speed = 10;
	act->max = 10;
	act->min = -10;
	add_obj(b, init_plane(init_vect(0.0, 0.0, 1.0), -10.0, init_col(COL_WHITESMOKE)));
	//Mur droite
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), -3.5, init_col(COL_BLUE)));
	//Mur gauche
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.5, init_col(COL_RED)));
	//Plafond
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), -3.5, init_col(COL_YELLOW)));
	//sol
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 3.5, init_col(COL_GREEN)));

	// add_obj(b, init_plane(init_vect(0.0, 0.0, 1.0), -10.0, init_col(COL_WHITESMOKE)));
	// //Mur droite
	// add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	// //Mur gauche
	// add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	// //Plafond
	// add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	// //sol
	// add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	// b->amb = init_col(1.0, 1.0, 1.0);

}

void	scene6(t_b *b)
{
	b->cam.pos = init_vect(0.0, 0.0, -15);

	add_lux(b, init_lux(init_vect(-2.0, 0.0, 0.0), init_col(COL_PURPLE), init_col(COL_PURPLE)));
	add_lux(b, init_lux(init_vect(-1.0, 1.0, 0.0), init_col(COL_BLUEVIOLET), init_col(COL_BLUEVIOLET)));
	add_lux(b, init_lux(init_vect(0.0, 2.0, 0.0), init_col(COL_SEAGREEN), init_col(COL_SEAGREEN)));
	add_lux(b, init_lux(init_vect(1.0, 1.0, 0.0), init_col(COL_LAWNGREEN), init_col(COL_LAWNGREEN)));
	add_lux(b, init_lux(init_vect(2.0, 0.0, 0.0), init_col(COL_YELLOWGREEN), init_col(COL_YELLOWGREEN)));
	add_lux(b, init_lux(init_vect(1.0, -1.0, 0.0), init_col(COL_YELLOW), init_col(COL_YELLOW)));
	add_lux(b, init_lux(init_vect(0.0, -2.0, 0.0), init_col(COL_LIGHTYELLOW), init_col(COL_LIGHTYELLOW)));
	add_lux(b, init_lux(init_vect(-1.0, -1.0, 0.0), init_col(COL_LIGHTPINK), init_col(COL_LIGHTPINK)));
	add_lux(b, init_lux(init_vect(0.0, 0.0, -5.0), init_col(COL_RED), init_col(COL_RED)));

	add_obj(b, init_sph(init_vect(0, 0, 8), init_col(1.0, 1.0, 1.0), 1.0));

	add_obj(b, init_plane(init_vect(0.0, 0.0, 1.0), -10.0, init_col(COL_WHITESMOKE)));
	//Mur droite
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	//Mur gauche
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	//Plafond
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	//sol
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	// add_obj(b, init_cyl(init_vect(2, 2, 3), init_col(0.0, 0.0, 1.0), init_vect(1.0, 0.0, 0.0), 1));
	// add_obj(b, init_cone(init_vect(0, 0, 5), init_col(0.0, 0.0, 1.0), init_vect(0.0, 1.0, 0.0), 1.0));
	// add_obj(b, init_cone(init_vect(0, 0, 10), init_col(0.0, 1.0, 0.0), init_vect(0.0, 1.0, 0.0), 1.0));
}


void	scene7(t_b *b)
{
	b->cam.pos = init_vect(0.0, 0.0, -15);

	//Interieur
	add_lux(b, init_lux(init_vect(-1.0, 0.0, 0.0), init_col(COL_PURPLE), init_col(COL_PURPLE)));
	add_lux(b, init_lux(init_vect(-0.5, 0.5, 0.0), init_col(COL_BLUEVIOLET), init_col(COL_BLUEVIOLET)));
	add_lux(b, init_lux(init_vect(0.0, 1.0, 0.0), init_col(COL_SEAGREEN), init_col(COL_SEAGREEN)));
	add_lux(b, init_lux(init_vect(0.5, 0.5, 0.0), init_col(COL_LAWNGREEN), init_col(COL_LAWNGREEN)));
	add_lux(b, init_lux(init_vect(1.0, 0.0, 0.0), init_col(COL_YELLOWGREEN), init_col(COL_YELLOWGREEN)));
	add_lux(b, init_lux(init_vect(0.5, -0.5, 0.0), init_col(COL_YELLOW), init_col(COL_YELLOW)));
	add_lux(b, init_lux(init_vect(0.0, -1.0, 0.0), init_col(COL_LIGHTYELLOW), init_col(COL_LIGHTYELLOW)));
	add_lux(b, init_lux(init_vect(-0.5, -0.5, 0.0), init_col(COL_LIGHTPINK), init_col(COL_LIGHTPINK)));
	//Exterieur
	add_lux(b, init_lux(init_vect(-2.0, 0.0, 0.0), init_col(COL_PURPLE), init_col(COL_PURPLE)));
	add_lux(b, init_lux(init_vect(-1.0, 1.0, 0.0), init_col(COL_BLUEVIOLET), init_col(COL_BLUEVIOLET)));
	add_lux(b, init_lux(init_vect(0.0, 2.0, 0.0), init_col(COL_SEAGREEN), init_col(COL_SEAGREEN)));
	add_lux(b, init_lux(init_vect(1.0, 1.0, 0.0), init_col(COL_LAWNGREEN), init_col(COL_LAWNGREEN)));
	add_lux(b, init_lux(init_vect(2.0, 0.0, 0.0), init_col(COL_YELLOWGREEN), init_col(COL_YELLOWGREEN)));
	add_lux(b, init_lux(init_vect(1.0, -1.0, 0.0), init_col(COL_YELLOW), init_col(COL_YELLOW)));
	add_lux(b, init_lux(init_vect(0.0, -2.0, 0.0), init_col(COL_LIGHTYELLOW), init_col(COL_LIGHTYELLOW)));
	add_lux(b, init_lux(init_vect(-1.0, -1.0, 0.0), init_col(COL_LIGHTPINK), init_col(COL_LIGHTPINK)));
	add_lux(b, init_lux(init_vect(0.0, 0.0, -5.0), init_col(COL_RED), init_col(COL_RED)));

	add_obj(b, init_sph(init_vect(0, 0, 8), init_col(1.0, 1.0, 1.0), 1.0));

	add_obj(b, init_plane(init_vect(0.0, 0.0, 1.0), -10.0, init_col(COL_WHITESMOKE)));
	//Mur droite
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	//Mur mid y
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 0, init_col(COL_WHITESMOKE)));
	//Mur mid x
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 0, init_col(COL_WHITESMOKE)));
	//Mur gauche
	add_obj(b, init_plane(init_vect(0.0, 1.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	//Plafond
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), -3.5, init_col(COL_WHITESMOKE)));
	//sol
	add_obj(b, init_plane(init_vect(1.0, 0.0, 0.0), 3.5, init_col(COL_WHITESMOKE)));
	// add_obj(b, init_cyl(init_vect(2, 2, 3), init_col(0.0, 0.0, 1.0), init_vect(1.0, 0.0, 0.0), 1));
	// add_obj(b, init_cone(init_vect(0, 0, 5), init_col(0.0, 0.0, 1.0), init_vect(0.0, 1.0, 0.0), 1.0));
	// add_obj(b, init_cone(init_vect(0, 0, 10), init_col(0.0, 1.0, 0.0), init_vect(0.0, 1.0, 0.0), 1.0));
}
