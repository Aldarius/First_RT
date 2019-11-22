/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:35:59 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 21:46:39 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_xy			fill_xy(double x, double y, t_color color)
{
	t_xy xy;

	xy.x = x;
	xy.y = y;
	xy.color = color;
	return (xy);
}

static t_xy		ray_sphere(t_snuffbox *m_s, t_viewer *view, int i)
{
	double	dis;
	t_xyz	oc;
	t_xy	t_t;

	oc = minus(view->o, m_s->spheres[i].center);
	dis = pow(2 * dot(oc, view->d), 2) -
	4 * dot(view->d, view->d) * (dot(oc, oc) -
	pow(m_s->spheres[i].radius, 2));
	if (dis < 0)
		return (fill_xy(INF, INF, fill_color(0, 0, 0, 0)));
	t_t.x = (-2 * dot(oc, view->d) + sqrt(dis)) /
	(2 * dot(view->d, view->d));
	t_t.y = (-2 * dot(oc, view->d) - sqrt(dis)) /
	(2 * dot(view->d, view->d));
	return (t_t);
}

void	closest(t_snuffbox *m_s, t_viewer *view, int flag)
{
	int			i;
	t_xy		t_t;

	i = -1;
	view->closest_t = INF;
	view->closest_sphere = fill_sphere(create_vector(0, 0, 0), 0,
	fill_color(0, 0, 0, 0), -1);
	while (m_s->spheres[++i].radius)
	{
		if (flag && m_s->spheres[i].is_lightball)
			continue;
		t_t = ray_sphere(m_s, view, i);
		if (t_t.x < view->t_max && t_t.x > view->t_min &&
		t_t.x < view->closest_t)
		{
			view->closest_t = t_t.x;
			view->closest_sphere = m_s->spheres[i];
		}
		if (t_t.y < view->t_max && t_t.y > view->t_min &&
		t_t.y < view->closest_t)
		{
			view->closest_t = t_t.y;
			view->closest_sphere = m_s->spheres[i];
		}
	}
}

t_color			trace(t_snuffbox *m_s, t_viewer view)
{
	t_xyz	n;
	t_color	local;
	t_color	reflect;

	closest(m_s, &view, 0);
	if (!view.closest_sphere.radius)
		return (fill_color(BACKGROUND));

	view.o = plus(view.o, a_vec(view.closest_t, view.d));
	n = minus(view.o, view.closest_sphere.center);
	n = a_vec(1 / sqrt(dot(n, n)), n);
	if (view.closest_sphere.is_lightball)
		return (view.closest_sphere.color);
	local = view.closest_sphere.color;
	local = mult_color(local, comp_light(m_s, view.o, n, &view));
	if (view.depth <= 0 || view.closest_sphere.reflective <= 0)
		return (local);
	view.d = reflect_ray(a_vec(-1, view.d), n);
	view.depth--;
	view.t_min = 0.001;
	view.t_max = INF;
	reflect = trace(m_s, view);
	reflect = mult_color(reflect, view.closest_sphere.reflective);
	local = mult_color(local, 1 - view.closest_sphere.reflective);
	return (sum_collors(&local, &reflect, 1));
}

double	veclen(t_xyz vector)
{
	return (sqrt(dot(vector, vector)));
}
