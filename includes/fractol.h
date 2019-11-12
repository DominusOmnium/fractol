/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:51 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/12 19:36:47 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "buttons.h"
# define WIDTH	1000
# define HEIGHT	1000

typedef enum
{
	fr_julia, fr_mandelbrot
}	t_fractal_type;
typedef struct	s_color
{
	char	r;
	char	g;
	char	b;
	char	a;
}				t_color;

typedef struct	s_fractal
{
	t_fractal_type	type;
	long double		x_start;
	long double		x_end;
	long double		y_start;
	long double		y_end;
	int				max_iter;
	double			p_width;
	double			p_height;
}				t_fractal;
typedef struct	s_view
{
	void		*mlx;
	void		*win;
	void		*img;
	t_color		*data_addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_fractal	fract;
}				t_view;

int				mouse_press(int b, int x, int y, t_view *v);
int				mouse_release(int b, int x, int y, t_view *v);
int				key_press(int k, t_view *v);
int				mouse_move(int x, int y, t_view *v);
t_view			*init_view(void);
void			init_fractal(t_fractal *f, char *fr);
void			setup_hooks(t_view *v);

#endif
