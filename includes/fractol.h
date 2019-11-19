/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:38:51 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/19 18:14:38 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <OpenCL/opencl.h>
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
	double	r;
	double	i;
}				t_complex;
typedef struct	s_mouse
{
	int			is_pressed;
	int			x;
	int			y;
	int			prev_x;
	int			prev_y;
}				t_mouse;
typedef struct	s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				output;
	size_t				local;
	size_t				global;
}				t_cl;
typedef struct	s_fractal
{
	t_fractal_type	type;
	double		r_start;
	double		r_end;
	double		i_start;
	double		i_end;
	int				max_iter;
	double		p_width;
	double		p_height;
	int				smooth;
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
	int			shift;
	t_mouse		mouse;
	t_fractal	fract;
	t_cl		cl;
}				t_view;

int				mouse_press(int b, int x, int y, t_view *v);
int				mouse_release(int b, int x, int y, t_view *v);
int				key_press(int k, t_view *v);
int				key_release(int k, t_view *v);
int				mouse_move(int x, int y, t_view *v);
int				init_view(t_view **view);
int				init_fractal(t_fractal *f, char *fr);
void			setup_hooks(t_view **v);
void			draw_fractal(t_view *v);
int				hsv_to_rgb(int h, int s, int v);
long double		mandelbrot(t_complex cxy, t_fractal f);
void			setup_mandelbrot(t_fractal *f);
long double		julia(int x, int y, t_complex cxy, t_view *v);
void			setup_julia(t_fractal *f);
t_complex		screen_to_complex(int x, int y, t_view *v);
char			*load_cl_file(char *fname);
void		draw_gpu_fractal(t_view *v);
void		init_kernel(t_cl *cl);
#endif
