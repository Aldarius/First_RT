/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 22:56:57 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 21:56:16 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_sphere		fill_sphere(t_xyz center, double r, t_color color, double spec)
{
	t_sphere sph;

	sph.center = center;
	sph.radius = r;
	sph.color = color;
	sph.spec = spec;
	sph.is_lightball = 0;
	sph.reflective = 0;
	return (sph);
}

t_xyz	create_vector(double x, double y, double z)
{
	return (fill_xyz(x, y, z, fill_color(0, 0, 0, 0)));
}

double	dot(t_xyz vector1, t_xyz vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y +
	vector1.z * vector2.z);
}

t_xyz	plus(t_xyz vector1, t_xyz vector2)
{
	t_xyz vec;

	vec.x = vector1.x + vector2.x;
	vec.y = vector1.y + vector2.y;
	vec.z = vector1.z + vector2.z;
	vec.color = vector1.color;
	return (vec);
}

t_xyz	minus(t_xyz vector1, t_xyz vector2)
{
	t_xyz vec;

	vec.x = vector1.x - vector2.x;
	vec.y = vector1.y - vector2.y;
	vec.z = vector1.z - vector2.z;
	vec.color = vector1.color;
	return (vec);
}
