/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 16:36:11 by lminta            #+#    #+#             */
/*   Updated: 2019/07/30 21:17:39 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	surf_to_text(t_snuffbox *m_s)
{
	int	i;

	i = FIRST_TEX - 1;
	while (++i < TOTAL_SURF && m_s->ren_type)
		if (m_s->sdl.surf_coll[i] != m_s->sdl.error_surf)
			if (!(m_s->sdl.tex_coll[i - FIRST_TEX] =
SDL_CreateTextureFromSurface(m_s->sdl.renderer, m_s->sdl.surf_coll[i])))
			{
				print_error("No texture for you: ", SDL_GetError());
				m_s->sdl.tex_coll[i - FIRST_TEX] = m_s->sdl.error_tex;
			}
}

void	print_tex(t_snuffbox *m_s)
{
	SDL_RenderClear(m_s->sdl.renderer);
	SDL_RenderCopy(m_s->sdl.renderer, m_s->sdl.current_tex, 0, 0);
	SDL_RenderPresent(m_s->sdl.renderer);
}
