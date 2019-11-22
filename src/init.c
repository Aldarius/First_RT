/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:56:35 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 14:30:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	nullificator(t_snuffbox *m_s)
{
	int	i;

	i = -1;
	while (++i < TOTAL_SURF)
		m_s->sdl.surf_coll[i] = m_s->sdl.error_surf;
	i = -1;
	while (++i < TOTAL_TEX)
		m_s->sdl.tex_coll[i] = m_s->sdl.error_tex;
	i = -1;
	while (++i < TOTAL_SPH)
	{
		m_s->spheres[i] = fill_sphere(create_vector(0, 0, 0), 0,
		fill_color(0, 0, 0, 0), -1);
		m_s->lights[i] = fill_light(NONE, 0, create_vector(0, 0, 0));
	}
}

static void	init_win_next(t_snuffbox *m_s)
{
	if (m_s->ren_type)
	{
		if (!(m_s->sdl.renderer =
		SDL_CreateRenderer(m_s->sdl.win, -1, m_s->ren_type)))
		{
			print_error("No renderer for you: ", SDL_GetError());
			exit(1);
		}
		SDL_SetRenderDrawColor(m_s->sdl.renderer, BACKGROUND);
		if (!(m_s->sdl.error_tex =
SDL_CreateTextureFromSurface(m_s->sdl.renderer, m_s->sdl.error_surf)))
			close_win(m_s, 1);
	}
	else
	{
		if (!(m_s->sdl.win_surf = SDL_GetWindowSurface(m_s->sdl.win)))
		{
			print_error("No surface for you: ", SDL_GetError());
			exit(1);
		}
		m_s->sdl.error_surf = opt_surf(m_s, m_s->sdl.error_surf);
	}
}

static void	init_const(t_snuffbox *m_s)
{
	nullificator(m_s);
	m_s->color = fill_color(255, 255, 255, 255);
	m_s->bd.xmax = WIN_W;
	m_s->bd.xmin = 0;
	m_s->bd.ymax = WIN_H;
	m_s->bd.ymin = 0;
}

void		init_win(t_snuffbox *m_s, int img_flag)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		print_error("No SDL for you: ", SDL_GetError());
		exit(1);
	}
	if (!(m_s->sdl.win =
	SDL_CreateWindow("First RT", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI)))
	{
		print_error("No window for you: ", SDL_GetError());
		exit(1);
	}
	if (!(IMG_Init(img_flag) & img_flag))
	{
		print_error("No IMG for you: ", IMG_GetError());
		exit(1);
	}
	if (!(m_s->sdl.error_surf = load_picture("res/error.bmp", BMP)))
		close_win(m_s, 1);
	init_win_next(m_s);
	init_const(m_s);
}

void		close_win(t_snuffbox *m_s, int code)
{
	int	i;

	SDL_FreeSurface(m_s->sdl.win_surf);
	i = -1;
	while (++i < TOTAL_SURF)
		if (m_s->sdl.surf_coll[i] != m_s->sdl.error_surf &&
		m_s->sdl.surf_coll[i])
			SDL_FreeSurface(m_s->sdl.surf_coll[i]);
	i = -1;
	while (++i < TOTAL_TEX)
		if (m_s->sdl.tex_coll[i] != m_s->sdl.error_tex &&
		m_s->sdl.tex_coll[i])
			SDL_DestroyTexture(m_s->sdl.tex_coll[i]);
	SDL_FreeSurface(m_s->sdl.error_surf);
	SDL_DestroyTexture(m_s->sdl.error_tex);
	SDL_DestroyWindow(m_s->sdl.win);
	SDL_DestroyRenderer(m_s->sdl.renderer);
	IMG_Quit();
	SDL_Quit();
	exit(code);
}
