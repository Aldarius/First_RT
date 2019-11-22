/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:15:20 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 21:12:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_error(const char *message, const char *error_message)
{
	if (!error_message || !message)
		write(2,
"FUCK MAN! YOUR WHOLE FUCKING PROGRAM IS FUCKING BROCKEN! FUCKING SHIT!\n", 71);
	else
	{
		write(2, message, ft_strlen(message));
		write(2, error_message, ft_strlen(error_message));
		write(2, "\n", 1);
	}
}

t_color		gradient(t_color *color1, t_color *color2, double length)
{
	t_color	grad;

	if (!length)
		return (*color2);
	grad.r = (color2->r - color1->r) / length;
	grad.g = (color2->g - color1->g) / length;
	grad.b = (color2->b - color1->b) / length;
	grad.br = (color2->br - color1->br) / length;
	return (grad);
}

t_color		sum_collors(t_color *color, t_color *grad, int count)
{
	t_color	result;

	result.r = color->r + grad->r * count;
	result.g = color->g + grad->g * count;
	result.b = color->b + grad->b * count;
	result.br = color->br + grad->br * count;
	if (result.br > 255)
		result.br = 255;
	if (result.r > 255)
	result.br = 255;
	if (result.g > 255)
	result.br = 255;
	if (result.b > 255)
	result.br = 255;
	result.vu_br = 1;
	return (result);
}

void		plot(t_snuffbox *m_s, int x, int y, t_color *cl)
{
	int		rgb;
	int		br;


	rgb = (cl->r + cl->g + cl->b) * (cl->br);
	if (rgb)
	{

		br = cl->br * cl->vu_br;
		if (br > 255)
			br = 255;
		SDL_SetRenderDrawColor(m_s->sdl.renderer,
		cl->r, cl->g, cl->b, br);
		SDL_RenderDrawPoint(m_s->sdl.renderer, x, y);
	}
}

t_color		fill_color(double red, double green, double blue, double alpha)
{
	t_color color;

	if (red < 0)
		color.r = 0;
	else if (red > 255)
		color.r = 255;
	else
		color.r = red;
	if (green < 0)
		color.g = 0;
	else if (green > 255)
		color.g = 255;
	else
		color.g = green;
	if (blue < 0)
		color.b = 0;
	else if (blue > 255)
		color.b = 255;
	else
		color.b = blue;
	color.br = alpha;
	color.vu_br = 1;
	return (color);
}
