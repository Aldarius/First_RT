/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:05:16 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 21:44:34 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"wolf3d.h"

t_xyz	a_vec(double a, t_xyz vector)
{
	t_xyz vec;

	vec.x = a * vector.x;
	vec.y = a * vector.y;
	vec.z = a * vector.z;
	vec.color = vector.color;
	return (vec);
}

t_light		fill_light(int type, double intens, t_xyz pos_dir)
{
	t_light	li;

	li.type = type;
	li.intens = intens;
	li.pos_dir = pos_dir;
	return (li);
}

double		comp_light(t_snuffbox *m_s, t_xyz p, t_xyz n, t_viewer *view)
{
	int			j;
	double		i;
	t_xyz		r;
	t_viewer	vi;

	j = -1;
	i = 0.0;
	vi.o = p;
	vi.t_min = 0.001;
	while (m_s->lights[++j].type != NONE)
	{
		if (m_s->lights[j].type == AMBIENT)
			i += m_s->lights[j].intens;
		else
		{
			if (m_s->lights[j].type == POINT)
			{
				vi.d = minus(m_s->lights[j].pos_dir, p);
				vi.t_max = 1;
			}
			else
			{
				vi.d = m_s->lights[j].pos_dir;
				vi.t_max = INF;
			}
			closest(m_s, &vi, 1);
			if (vi.closest_sphere.radius)
				continue;
			if (dot(n, vi.d) > 0)
				i += m_s->lights[j].intens * dot(n, vi.d) /
				(sqrt(dot(n, n)) * veclen(vi.d));
			if (view->closest_sphere.spec != -1)
			{
				r = minus(a_vec(2 * dot(n, vi.d), n), vi.d);
				if (dot(r, a_vec(-1, view->d)) > 0)
					i += m_s->lights[j].intens * pow((dot(r, a_vec(-1, view->d)))
					/ (sqrt(dot(r, r)) * veclen(a_vec(-1, view->d))),
					view->closest_sphere.spec);
			}
		}
	}
	return (i);
}
