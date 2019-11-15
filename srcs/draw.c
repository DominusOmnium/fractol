/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:24:18 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/15 15:09:34 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel_img(int x, int y, int color, t_view *v)
{
	int			i;

	i = x + y * v->line_size / 4;
	(v->data_addr)[i] = color;
}

t_complex	screen_to_complex(int x, int y, t_view *v)
{
	t_complex	c;

	c.i = v->fract.i_start + y * v->fract.p_height;
	c.r = v->fract.r_start + x * v->fract.p_width;
	return (c);
}

void		draw_fractal(t_view *v)
{
	int			i;
	int			j;
	long double	n;
	t_complex	c;

	i = 0;
	if (v->fract.type == fr_julia)
		c = screen_to_complex(v->mouse.x, v->mouse.y, v);
	while (i < HEIGHT)
	{
		if (v->fract.type == fr_mandelbrot)
			c.i = v->fract.i_start + i * v->fract.p_height;
		j = 0;
		while (j < WIDTH)
		{
			if (v->fract.type == fr_mandelbrot)
				c.r = v->fract.r_start + j * v->fract.p_width;
			if (v->fract.type == fr_mandelbrot)
				n = mandelbrot(c, v->fract);
			else if (v->fract.type == fr_julia)
				n = julia(j, i, c, v);
			put_pixel_img(j, i, hsv_to_rgb(255.0 * n / v->fract.max_iter, 255, 255 * (n < v->fract.max_iter)), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}
