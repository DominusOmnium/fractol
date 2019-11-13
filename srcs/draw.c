/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:24:18 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/13 17:40:51 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		put_pixel_img(int x, int y, int color, t_view *v)
{
	int			i;

	i = x + y * v->line_size / 4;
	(v->data_addr)[i] = color;
}

static int		mandelbrot(long double cx, long double cy, int max_iter)
{
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;
	int		n;

	zx = 0;
	zy = 0;
	zx2 = 0;
	zy2 = 0;
	n = 0;
	while (zx2 + zy2 < 4 && n < max_iter)
	{
		zy = 2 * zx * zy + cy;
		zx = zx2 - zy2 + cx;
		zx2 = zx * zx;
		zy2 = zy * zy;
		n++;
	}
	return (n);
}

static int	calc_color(int m, int max_iter)
{
	int color;

	color = 255 - 255.0 * (1.0 - m / max_iter);
	return (color | color << 8 | color << 16);
}

void			draw_fractal(t_view *v)
{
	int			i;
	int			j;
	long double	cy;

	i = 0;
	while (i < HEIGHT)
	{
		cy = v->fract.y_start + i * v->fract.p_height;
		j = 0;
		while (j < WIDTH)
		{
			put_pixel_img(j, i, calc_color(mandelbrot(v->fract.x_start + j * v->fract.p_width, cy, v->fract.max_iter), v->fract.max_iter), v);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}
