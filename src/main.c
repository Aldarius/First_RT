/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:00:37 by lminta            #+#    #+#             */
/*   Updated: 2019/09/03 15:36:39 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(void)
{
	t_snuffbox	m_s;
	int			running;
	//t_xy		xy1, xy2;
	int			x = -WIN_W / 2 - 1;
	int			y = -WIN_H / 2 - 1;
	t_color		color;

	running = 1;
	m_s.ren_type = SDL_RENDERER_SOFTWARE;
	init_win(&m_s, IMG_INIT_PNG);
	SDL_SetRenderDrawBlendMode(m_s.sdl.renderer, SDL_BLENDMODE_BLEND);
	m_s.view.o = create_vector(0, 0, 0);
	m_s.view.t_min = 1;
	m_s.view.t_max = INF;
	m_s.spheres[1] = fill_sphere(create_vector(0, -400, 1200), 100,
	fill_color(255, 0, 0, 255), 50);
	m_s.spheres[1].reflective = 0.15;
	m_s.spheres[2] = fill_sphere(create_vector(0, 300, 1200), 100,
	fill_color(255, 255, 0, 255), 100);
	m_s.spheres[2].reflective = 0.4;
	m_s.spheres[3] = fill_sphere(create_vector(300, 270, 1200), 50,
	fill_color(255, 0, 255, 255), 10);
	m_s.spheres[3].reflective = 0.15;
	m_s.spheres[4] = fill_sphere(create_vector(-400, -400, 1200), 150,
	fill_color(255, 255, 255, 255), 1000);
	m_s.spheres[4].reflective = 0.9;
	m_s.spheres[5] = fill_sphere(create_vector(0, -100400, 1200), 100000,
	fill_color(93, 161, 48, 255), 1);
	m_s.spheres[5].reflective = 0;

	m_s.lights[0] = fill_light(AMBIENT, 0.1, create_vector(0, 0, 0));
	m_s.lights[1] = fill_light(POINT, 0.3, create_vector(400, 200, 1250));
	m_s.spheres[0] = fill_sphere(create_vector(400, 200, 1250), 10,
	fill_color(255, 255, 255, 255), 1);
	m_s.spheres[0].is_lightball = 1;
	m_s.lights[2] = fill_light(DIRECT, 0.6, create_vector(-1, 1, -1));
	x = -WIN_W / 2 - 1;
	SDL_SetRenderDrawColor(m_s.sdl.renderer, BACKGROUND);
	SDL_RenderClear(m_s.sdl.renderer);
	while (++x < WIN_W / 2)
	{
		y = -WIN_H / 2 - 1;
		while (++y < WIN_H / 2)
		{
			m_s.view.d = canvas_to_screen(x, y);
			m_s.view.depth = 3;
			color = trace(&m_s, m_s.view);
			plot(&m_s, WIN_W / 2 + x, WIN_H / 2 - y, &color);
		}
	}
	SDL_RenderPresent(m_s.sdl.renderer);
	while (running)
	{
		while (SDL_PollEvent(&m_s.sdl.event))
		{
			if (m_s.sdl.event.type == SDL_QUIT ||
			(m_s.sdl.event.type == SDL_KEYDOWN &&
			m_s.sdl.event.key.keysym.sym == SDLK_ESCAPE))
				running = 0;
		}
	}
	//close_win(&m_s, 0);
	return (0);
}
