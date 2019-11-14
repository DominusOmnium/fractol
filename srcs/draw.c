/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:24:18 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/14 18:04:30 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			put_pixel_img(int x, int y, int color, t_view *v)
{
	int			i;

	i = x + y * v->line_size / 4;
	(v->data_addr)[i] = color;
}

static t_complex	screen_to_complex(int x, int y, t_view *v)
{
	t_complex	c;

	c.i = v->fract.y_start + y * v->fract.p_height;
	c.r = v->fract.x_start + x * v->fract.p_width;
	return (c);
}

static int			mandelbrot(t_complex cxy, t_fractal f)
{
	t_complex	c;
	t_complex	c2;
	int			n;

	c.r = 0;
	c.i = 0;
	c2.r = 0;
	c2.i = 0;
	n = 0;
	while (c2.r + c2.i < 4 && n < f.max_iter)
	{
		c.i = 2 * c.r * c.i + cxy.i;
		c.r = c2.r - c2.i + cxy.r;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	return (n);
}

static int			julia(int x, int y, t_complex cxy, t_view *v)
{
	t_complex	c;
	t_complex	c2;
	int			n;

	c = screen_to_complex(x, y, v);
	c2.r = c.r * c.r;
	c2.i = c.i * c.i;
	n = 0;
	while (c2.r + c2.i < 4 && n < v->fract.max_iter)
	{
		c.i = 2 * c.r * c.i + cxy.i;
		c.r = c2.r - c2.i + cxy.r;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	return (n);
}

void				draw_fractal(t_view *v)
{
	int			i;
	int			j;
	int			n;
	t_complex	c;

	i = 0;
	if (v->fract.type == fr_julia)
		c = screen_to_complex(v->mouse.x, v->mouse.y, v);
	while (i < HEIGHT)
	{
		if (v->fract.type == fr_mandelbrot)
			c.i = v->fract.y_start + i * v->fract.p_height;
		j = 0;
		while (j < WIDTH)
		{
			if (v->fract.type == fr_mandelbrot)
				c.r = v->fract.x_start + j * v->fract.p_width;
			if (v->fract.type == fr_mandelbrot)
				n = mandelbrot(c, v->fract);
			else if (v->fract.type == fr_julia)
				n = julia(j, i, c, v);
			put_pixel_img(j, i, hsv_to_rgb(n % 360, 255 * ((long double)n / v->fract.max_iter),
											255 * (n < v->fract.max_iter)), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}
