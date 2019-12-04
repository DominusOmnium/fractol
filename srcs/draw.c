/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:24:18 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/04 12:55:57 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel_img(int x, int y, int color, t_view *v)
{
	int			i;

	i = x + y * v->line_size / 4;
	(v->data_addr)[i] = color;
}

t_complex	screen_to_complex(int x, int y, t_fractal fract)
{
	t_complex	c;

	c.i = fract.i_start + y * fract.p_height;
	c.r = fract.r_start + x * fract.p_width;
	return (c);
}

static void	draw_cpu1(t_view *v, t_complex c, int i, int j)
{
	long double	n;
	t_color		color;

	n = 0;
	if (v->fract.type == fr_mandelbrot || v->fract.type == fr_newton)
		c.r = v->fract.r_start + j * v->fract.p_width;
	if (v->fract.type == fr_mandelbrot)
		n = mandelbrot(c, v->fract);
	else if (v->fract.type == fr_julia)
		n = julia(j, i, c, v->fract);
	color.value = hsv_to_rgb(255.0 * n / v->fract.max_iter,
							255, 255 * (n < v->fract.max_iter));
	if (v->fract.type == fr_newton)
	{
		n = newton(c, v->fract);
		color = (t_color){{(int)(n * 20) % 255, (int)(n * 10) % 255, 0, 0}};
	}
	put_pixel_img(j, i, color.value, v);
}

static void	draw_cpu(t_view *v)
{
	int			i;
	int			j;
	t_complex	c;

	if (v->fract.type == fr_julia)
		c = screen_to_complex(v->mouse.x, v->mouse.y, v->fract);
	i = -1;
	while (++i < HEIGHT)
	{
		if (v->fract.type == fr_mandelbrot || v->fract.type == fr_newton)
			c.i = v->fract.i_start + i * v->fract.p_height;
		j = -1;
		while (++j < WIDTH)
		{
			draw_cpu1(v, c, i, j);
		}
	}
}

void		draw_fractal(t_view *v)
{
	if (v->help)
		return ;
	if (v->draw_type == gpu_parallel)
		draw_parallel(v, true);
	else if (v->draw_type == cpu_parallel)
		draw_parallel(v, false);
	else
		draw_cpu(v);
	mlx_clear_window(v->mlx, v->win);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	draw_fract_gui(v);
}
