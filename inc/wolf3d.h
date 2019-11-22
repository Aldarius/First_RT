/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:50:50 by lminta            #+#    #+#             */
/*   Updated: 2019/08/08 22:10:30 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIN_W		1200
# define WIN_H		1200
# define CAN_W		1
# define CAN_H		1
# define TOTAL_SURF	256
# define TOTAL_TEX	256
# define FIRST_TEX	6
# define TOTAL_SPH	32
# define INF		50000
# define BACKGROUND 117, 187, 253, 255

# include <SDL.h>
# include <SDL_image.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <math.h>
# include "get_next_line.h"

enum				e_lighy_type
{
	NONE,
	AMBIENT,
	DIRECT,
	POINT
};

enum				e_img_type
{
	BMP,
	IMG
};

enum				e_key_surfaces
{
	DEFAULT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	TOTAL
};

typedef struct	s_borders
{
	double		xmin;
	double		ymin;
	double		xmax;
	double		ymax;

}				t_borders;

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
	double		br;
	double		vu_br;
}				t_color;

typedef struct	s_xy
{
	double		x;
	double		y;
	double		intery;
	t_color		color;
}				t_xy;

typedef struct	s_xyz
{
	double		x;
	double		y;
	double		z;
	t_color		color;
}				t_xyz;

typedef struct	s_steep_grad
{
	int			steep;
	double		grad;
}				t_steep_grad;

typedef struct	s_sphere
{
	t_xyz		center;
	double		radius;
	t_color		color;
	double		spec;
	double		reflective;
	char		is_lightball;

}				t_sphere;

typedef struct	s_light
{
	int			type;
	double		intens;
	t_xyz		pos_dir;
}				t_light;

typedef struct	s_viewer
{
	t_xyz		o;
	t_xyz		d;
	double		t_min;
	double		t_max;
	double		closest_t;
	t_sphere	closest_sphere;
	int			depth;
}				t_viewer;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*win_surf;
	SDL_Surface		*error_surf;
	SDL_Texture		*error_tex;
	SDL_Renderer	*renderer;
	SDL_Surface		*current_surf;
	SDL_Texture		*current_tex;
	SDL_Surface		*surf_coll[TOTAL_SURF];
	SDL_Texture		*tex_coll[TOTAL_TEX];
	SDL_Event		event;
}					t_sdl;

typedef struct		s_snuffbox
{
	t_sphere		spheres[TOTAL_SPH];
	t_light			lights[TOTAL_SPH];
	t_color			color;
	t_sdl			sdl;
	int				ren_type;
	t_borders		bd;
	t_viewer		view;
}					t_snuffbox;

int					ipart(double x);
int					ft_round(double x);
double				fpart(double x);
double				rfpart(double x);
void				ft_swap(double *a, double *b);
void				init_win(t_snuffbox *m_s, int img_flag);
void				close_win(t_snuffbox *main_struct, int code);
void				print_picture(t_snuffbox *m_s);
SDL_Surface			*load_picture(const char *filename, int type);
void				print_error(const char *message, const char *error_message);
void				load_dir(t_snuffbox *m_s, const char *dirname, int type);
SDL_Surface			*opt_surf(t_snuffbox *m_s, SDL_Surface *in);
void				opt_dir(t_snuffbox *m_s);
void				surf_to_text(t_snuffbox *m_s);
void				print_tex(t_snuffbox *m_s);
void				plot(t_snuffbox *m_s, int x, int y, t_color *cl);
void				draw_line(t_snuffbox *m_s, t_xy *xy0, t_xy *xy1);
t_color				gradient(t_color *color1, t_color *color2, double length);
t_color				sum_collors(t_color *color, t_color *grad, int count);
t_color				fill_color(double red, double green, double blue, double alpha);
void				ft_swap_color(t_color *a, t_color *b);
t_borders			fill_borders(double xmin, double ymin, double xmax, double ymax);
void				clip(t_snuffbox *m_s, t_xy xy1, t_xy xy2);
t_snuffbox			twist_roll_up(t_snuffbox *m_s, t_borders bd);
t_xyz				fill_xyz(double x, double y, double z, t_color color);
t_xyz				canvas_to_screen(double x, double y);
t_xyz				create_vector(double x, double y, double z);
double				dot(t_xyz vector1, t_xyz vector2);
t_sphere			fill_sphere(t_xyz center, double r, t_color color, double spec);
t_xyz				plus(t_xyz vector1, t_xyz vector2);
t_xyz				minus(t_xyz vector1, t_xyz vector2);
t_xy				fill_xy(double x, double y, t_color color);
t_color				trace(t_snuffbox *m_s, t_viewer view);
t_light				fill_light(int type, double intens, t_xyz pos_dir);
t_xyz				a_vec(double a, t_xyz vector);
double		comp_light(t_snuffbox *m_s, t_xyz p, t_xyz n, t_viewer *view);
double				veclen(t_xyz vector);
void				closest(t_snuffbox *m_s, t_viewer *view, int flag);
t_xyz				reflect_ray(t_xyz r, t_xyz n);
t_color				mult_color(t_color color, double a);

#endif
