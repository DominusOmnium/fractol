/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:26:52 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/14 18:02:18 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calc_color(int m, int max_iter)
{
	int color;

	color = 255 - 255.0 * (1.0 - m / (long double)max_iter);
	return (color | color << 8 | color << 16);
}

int				hsv_to_rgb(int h, int s, int v)
{
	int		hi;
	int		vmin;
	int		a;
	int		vinc;
	int		vdec;

	hi = h % 6;
	vmin = (100 - s) * v / 100.0;
	a = (v - vmin) * (h % 60) / 60.0;
	vinc = vmin + a;
	vdec = v - a;
	if (h % 6 == 0)
		return ((t_color){vmin, vinc, v, 0}.value);
	if (h % 6 == 1)
		return ((t_color){vmin, v, vdec, 0}.value);
	if (h % 6 == 2)
		return ((t_color){vinc, v, vmin, 0}.value);
	if (h % 6 == 3)
		return ((t_color){v, vdec, vmin, 0}.value);
	if (h % 6 == 4)
		return ((t_color){v, vmin, vinc, 0}.value);
	return ((t_color){vdec, vmin, v, 0}.value);
}
