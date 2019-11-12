/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:47:25 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/12 19:37:38 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(double cx, double cy, int max_iter)
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

int		calc_color(int m)
{
	int color;

	color = 255 - 255.0 * (1.0 - m / 50.0);
	return (color | color << 8 | color << 16);
}

void	draw_fractal(t_view *v)
{
	int		i;
	int		j;
	double	cy;
	
	v->fract.p_width = (v->fract.x_end - v->fract.x_start) / WIDTH;
    v->fract.p_height = (v->fract.y_end - v->fract.y_start) / HEIGHT;
	i = 0;
	while (i < HEIGHT)
	{
		cy = v->fract.y_start + i * v->fract.p_height;
		j = 0;
		while (j < WIDTH)
		{
			mlx_pixel_put(v->mlx, v->win, j, i, calc_color(mandelbrot(v->fract.x_start + j * v->fract.p_width, cy, v->fract.max_iter)));
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_view	*v;

	v = init_view();
	init_fractal(&(v->fract), av[1]);
	draw_fractal(v);
	setup_hooks(v);
	mlx_loop(v->win);
}
