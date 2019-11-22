/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:25:19 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 21:23:55 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_xyz	reflect_ray(t_xyz r, t_xyz n)
{
	return (minus(a_vec(2*dot(n, r), n), r));
}

t_color	mult_color(t_color color, double a)
{
	if (color.r * a < 0)
		color.r = 0;
	else if (color.r * a > 255)
		color.r = 255;
	else
		color.r = color.r * a;
	if (color.g * a < 0)
		color.g = 0;
	else if (color.g * a > 255)
		color.g = 255;
	else
		color.g = color.g * a;
	if (color.b * a < 0)
		color.b = 0;
	else if (color.b * a > 255)
		color.b = 255;
	else
		color.b = color.b * a;
	color.br = color.br;
	color.vu_br = color.vu_br;
	return (color);
}
