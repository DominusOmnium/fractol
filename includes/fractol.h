/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:51 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/14 18:02:24 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "buttons.h"
# include "def_values.h"

typedef enum
{
	fr_julia, fr_mandelbrot
}	t_fractal_type;
typedef struct	s_rgba
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
	uint8_t		a;
}				t_rgba;
typedef union	u_color
{
	t_rgba		rgba;
	int			value;
}				t_color;
typedef struct	s_complex
{
	long double	r;
	long double	i;
}				t_complex;
typedef struct	s_mouse
{
	t_bool		is_pressed;
	int			x;
	int			y;
	int			prev_x;
	int			prev_y;
}				t_mouse;
typedef struct	s_fractal
{
	t_fractal_type	type;
	long double		x_start;
	long double		x_end;
	long double		y_start;
	long double		y_end;
	int				max_iter;
	long double		p_width;
	long double		p_height;
}				t_fractal;
typedef struct	s_view
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data_addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_mouse		mouse;
	t_fractal	fract;
}				t_view;

int				mouse_press(int b, int x, int y, t_view *v);
int				mouse_release(int b, int x, int y, t_view *v);
int				key_press(int k, t_view *v);
int				mouse_move(int x, int y, t_view *v);
int				init_view(t_view **view);
int				init_fractal(t_fractal *f, char *fr);
void			setup_hooks(t_view *v);
void			draw_fractal(t_view *v);
int				hsv_to_rgb(int h, int s, int v);
#endif
