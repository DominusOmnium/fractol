/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:33:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/21 15:01:13 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	newton(t_complex c, t_fractal f)
{
	t_complex	t;
	t_complex	t2;
	int			n;
	long double	p;

	n = 0;
	while ((c.r * c.r + c.i * c.i < 10000) && (n < f.max_iter))
	{
		t.r = c.r;
		t.i = c.i;
		t2.i = t.i * t.i;
		t2.r = t.r * t.r;
		p = (t2.r + t2.i) * (t2.r + t2.i);
		c.r = 2.0 / 3.0 * t.r + (t2.r - t2.i) / (3.0 * p);
		c.i = 2.0 / 3.0 * t.i * (1.0 - t.r / p);
		n++;
	}
	return ((long double)n + (1.0 - log2(log2((double)((c.r * c.r + c.i * c.i) /
											(f.smooth == 1 ? 1 : 10000))))));
}

void		setup_newton(t_fractal *f)
{
	f->type = fr_newton;
	f->r_start = -1;
	f->r_end = 1;
	f->i_start = 0 - (f->r_end - f->r_start) / 2 * HEIGHT / (double)WIDTH;
	f->i_end = 0 + (f->r_end - f->r_start) / 2 * HEIGHT / (double)WIDTH;
	f->p_width = (f->r_end - f->r_start) / WIDTH;
	f->p_height = (f->i_end - f->i_start) / HEIGHT;
}
