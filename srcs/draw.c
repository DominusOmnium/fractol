/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:24:18 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/20 17:57:32 by dkathlee         ###   ########.fr       */
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

static void	draw_cpu(t_view *v)
{
	int			i;
	int			j;
	long double	n;
	t_complex	c;

	
	if (v->fract.type == fr_julia)
		c = screen_to_complex(v->mouse.x, v->mouse.y, v);
	i = -1;
	while (++i < HEIGHT)
	{
		if (v->fract.type == fr_mandelbrot)
			c.i = v->fract.i_start + i * v->fract.p_height;
		j = -1;
		while (++j < WIDTH)
		{
			if (v->fract.type == fr_mandelbrot)
				c.r = v->fract.r_start + j * v->fract.p_width;
			if (v->fract.type == fr_mandelbrot)
				n = mandelbrot(c, v->fract);
			else if (v->fract.type == fr_julia)
				n = julia(j, i, c, v);
			put_pixel_img(j, i, hsv_to_rgb(255.0 * n / v->fract.max_iter,
									255, 255 * (n < v->fract.max_iter)), v);
		}
	}
}

static void	draw_gui(t_view *v)
{
	char	*tmp;

	mlx_string_put(v->mlx, v->win, 5, 5, COLOR_TEXT_DEF, "Max iterations: ");
	tmp = ft_itoa(v->fract.max_iter);
	mlx_string_put(v->mlx, v->win, 200, 5, COLOR_TEXT_DEF, tmp);
	ft_memdel((void**)&tmp);
	mlx_string_put(v->mlx, v->win, 5, 30, COLOR_TEXT_DEF, "Press H for help");
}

void		draw_fractal(t_view *v)
{
	if (v->draw_type == gpu_parallel)
		draw_parallel(v, true);
	else if (v->draw_type == cpu_parallel)
		draw_parallel(v, false);
	else
		draw_cpu(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	draw_gui(v);
}
