/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:26:52 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/15 11:26:08 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calc_color(int m, int max_iter)
{
	int color;

	color = 255 - 255.0 * (1.0 - m / (long double)max_iter);
	return (color | color << 8 | color << 16);
}

int				hsv_to_rgb1(int h, int s, int v)
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
	if (h == 0)
		return ((t_color){vmin, vinc, v, 0}.value);
	if (h == 1)
		return ((t_color){vmin, v, vdec, 0}.value);
	if (h == 2)
		return ((t_color){vinc, v, vmin, 0}.value);
	if (h == 3)
		return ((t_color){v, vdec, vmin, 0}.value);
	if (h == 4)
		return ((t_color){v, vmin, vinc, 0}.value);
	return ((t_color){vdec, vmin, v, 0}.value);
}

int hsv_to_rgb(int h, int s, int v)
{
    unsigned char	region;
	unsigned char	remainder;
	unsigned char	p;
	unsigned char	q;
	unsigned char	t;

    if (s == 0)
		return ((t_color){v, v, v, 0}.value);

    region = h / 43;
    remainder = (h - (region * 43)) * 6; 

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		return ((t_color){p, t, v, 0}.value);
	if (region == 1)
		return ((t_color){p, v, q, 0}.value);
	if (region == 2)
		return ((t_color){t, v, p, 0}.value);
	if (region == 3)
		return ((t_color){v, q, p, 0}.value);
	if (region == 4)
		return ((t_color){v, p, t, 0}.value);
	return ((t_color){q, p, v, 0}.value);
}
