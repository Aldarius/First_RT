/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_surf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:18:43 by lminta            #+#    #+#             */
/*   Updated: 2019/07/30 21:18:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

SDL_Surface	*load_picture(const char *filename, int type)
{
	SDL_Surface	*surf;

	if (type == BMP)
		if (!(surf = SDL_LoadBMP(filename)))
			print_error("No picture for you: ", SDL_GetError());
	if (type == IMG)
		if (!(surf = IMG_Load(filename)))
			print_error("No picture for you: ", IMG_GetError());
	return (surf);
}

void		print_picture(t_snuffbox *m_s)
{
	SDL_Rect stretch;

	stretch.x = 0;
	stretch.y = 0;
	stretch.w = WIN_W;
	stretch.h = WIN_H;
	SDL_BlitScaled(m_s->sdl.current_surf, 0, m_s->sdl.win_surf, &stretch);
	SDL_UpdateWindowSurface(m_s->sdl.win);
}

SDL_Surface	*opt_surf(t_snuffbox *m_s, SDL_Surface *in)
{
	SDL_Surface	*opt;

	if (!in)
		return (0);
	if (!(opt = SDL_ConvertSurface(in, m_s->sdl.win_surf->format, 0)))
	{
		print_error("No optimization for you: ", SDL_GetError());
		close_win(m_s, 1);
	}
	SDL_FreeSurface(in);
	return (opt);
}

void		load_dir(t_snuffbox *m_s, const char *dirname, int type)
{
	struct dirent	*name_buff;
	char			*buff;
	DIR				*res;
	int				i;

	if (!(res = opendir(dirname)))
	{
		print_error("No folder for you", ":(");
		close_win(m_s, 1);
	}
	while ((name_buff = readdir(res)))
		if (name_buff->d_type == 8)
		{
			buff = ft_strjoin(dirname, name_buff->d_name);
			i = ft_atoi(name_buff->d_name);
			if (m_s->sdl.surf_coll[i] == m_s->sdl.error_surf)
				if (!(m_s->sdl.surf_coll[i] = load_picture(buff, type)))
					m_s->sdl.surf_coll[i] = m_s->sdl.error_surf;
			free(buff);
			++i;
		}
	closedir(res);
}

void		opt_dir(t_snuffbox *m_s)
{
	int	i;

	i = -1;
	if (!m_s->ren_type)
		while (++i < TOTAL_SURF)
			if (m_s->sdl.surf_coll[i] != m_s->sdl.error_surf)
				m_s->sdl.surf_coll[i] = opt_surf(m_s, m_s->sdl.surf_coll[i]);
}
