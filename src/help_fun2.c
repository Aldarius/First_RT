/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:38:06 by lminta            #+#    #+#             */
/*   Updated: 2019/08/07 14:34:48 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_swap_color(t_color *a, t_color *b)
{
	t_color buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

t_borders	fill_borders(double xmin, double ymin, double xmax, double ymax)
{
	t_borders borders;

	borders.xmin = xmin;
	borders.ymin = ymin;
	borders.xmax = xmax;
	borders.ymax = ymax;
	return (borders);
}

t_snuffbox	twist_roll_up(t_snuffbox *m_s, t_borders bd)
{
	t_snuffbox roll_up;

	roll_up = *m_s;
	roll_up.bd = bd;
	return	(roll_up);
}

t_xyz		fill_xyz(double x, double y, double z, t_color color)
{
	t_xyz xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	xyz.color = color;
	return (xyz);
}

t_xyz		canvas_to_screen(double x, double y)
{
	double	Vw;
	double	Vh;
	double	Cw;
	double	Ch;

	Vw = CAN_W;
	Vh = CAN_H;
	Cw = WIN_W;
	Ch = WIN_H;
	return (create_vector(x * Vw / Cw, y * Vh / Ch, 1));
}
