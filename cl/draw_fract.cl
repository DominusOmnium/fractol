#include "includes/def_values.h"

typedef struct	s_complex
{
	double	i;
	double	r;
}				t_complex;
typedef struct	s_complexl
{
	long double	i;
	long double	r;
}				t_complexl;

static int 			hsv_to_rgb(int h, int s, int v)
{
    unsigned char	region;
	unsigned char	remainder;
	unsigned char	p;
	unsigned char	q;
	unsigned char	t;

    if (s == 0)
		return (v | v << 8 | v << 16);
    region = h / 43;
    remainder = (h - (region * 43)) * 6; 
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
		return (p | t << 8 | v << 16);
	if (region == 1)
		return (p | v << 8 | q << 16);
	if (region == 2)
		return (t | v << 8 | p << 16);
	if (region == 3)
		return (v | q << 8 | p << 16);
	if (region == 4)
		return (v | p << 8 | t << 16);
	return (q | p << 8 | v << 16);
}

static t_complex	screen_to_complex(	int		x,
										int		y,
										double	i_start,
										double	r_start,
										double	p_height,
										double	p_width)
{
	t_complex	c;

	c.i = i_start + y * p_height;
	c.r = r_start + x * p_width;
	return (c);
}

static t_complexl	screen_to_complexl(	int			x,
										int			y,
										long double	i_start,
										long double	r_start,
										long double	p_height,
										long double	p_width)
{
	t_complexl	c;

	c.i = i_start + y * p_height;
	c.r = r_start + x * p_width;
	return (c);
}

__kernel void draw_fract(__global char	*output,
						int				max_iter,
						int				fr_type,
						int				smooth,
						int				x,
						int				y,
						double			i_start,
						double			r_start,
						double			p_height,
						double			p_width)
{
	t_complex	cxy;
	t_complex	c;
	t_complex	c2;
	double		m;
	int			n;
	int			i;
	int			j;
	int			gid;

	gid = get_global_id(0);
	if (gid < 0 || gid >= HEIGHT * WIDTH)
		return ;
	i = gid / WIDTH;
	j = gid % WIDTH;
	if (fr_type == 0)
	{
		c = screen_to_complex(j, i, i_start, r_start, p_height, p_width);
		cxy = screen_to_complex(x, y, i_start, r_start, p_height, p_width);
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n = 0;
		while (c2.r + c2.i < 256 && n < max_iter)
		{
			c.i = 2 * c.r * c.i + cxy.i;
			c.r = c2.r - c2.i + cxy.r;
			c2.r = c.r * c.r;
			c2.i = c.i * c.i;
			n++;
		}
	}
	else if (fr_type == 1)
	{
		c.r = 0;
		c.i = 0;
		c2.r = 0;
		c2.i = 0;
		cxy.i = i_start + i * p_height;
		cxy.r = r_start + j * p_width;
		n = 0;
		while (c2.r + c2.i <= 256 && n < max_iter)
		{
			c.i = 2 * c.r * c.i + cxy.i;
			c.r = c2.r - c2.i + cxy.r;
			c2.r = c.r * c.r;
			c2.i = c.i * c.i;
			n++;
		}
	}
	else
	{
		t_complexl	t;
		t_complexl	t2;
		int			q;
		double		p;

		c.r = (r_start + j * p_width);
		c.i = (i_start + i * p_height);
		n = 0;
		q = 100000;
		while ((c.r*c.r + c.i*c.i < q)&& (n < max_iter))
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
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		m = (double)n + (1.0 - log2(log2((c2.r + c2.i) / (smooth == 1 ? 1 : q))));
		int g = (int)(m * 10) % 255;
		int b = (int)(m * 20) % 255;
		((__global unsigned int*)output)[gid] = b | g << 8;
		return ;
	}
	m = (double)n + (smooth == 1 ? (1.0 - log2(log2(c2.r + c2.i))) : 0);
	((__global unsigned int*)output)[gid] = hsv_to_rgb(255 * m / max_iter, 255, 255 * (m < max_iter));
}

__kernel void draw_fract_long(__global char	*output,
							int				max_iter,
							int				fr_type,
							int				smooth,
							int				x,
							int				y,
							long double		i_start,
							long double		r_start,
							long double		p_height,
							long double		p_width)
{
	t_complexl	cxy;
	t_complexl	c;
	t_complexl	c2;
	long double	m;
	int			n;
	int			i;
	int			j;
	int			gid;

	gid = get_global_id(0);
	if (gid < 0 || gid >= HEIGHT * WIDTH)
		return ;
	i = gid / WIDTH;
	j = gid % WIDTH;
	if (fr_type == 0)
	{
		c = screen_to_complexl(j, i, i_start, r_start, p_height, p_width);
		cxy = screen_to_complexl(x, y, i_start, r_start, p_height, p_width);
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n = 0;
		while (c2.r + c2.i < 256 && n < max_iter)
		{
			c.i = 2 * c.r * c.i + cxy.i;
			c.r = c2.r - c2.i + cxy.r;
			c2.r = c.r * c.r;
			c2.i = c.i * c.i;
			n++;
		}
	}
	else if (fr_type == 1)
	{
		c.r = 0;
		c.i = 0;
		c2.r = 0;
		c2.i = 0;
		cxy.i = i_start + i * p_height;
		cxy.r = r_start + j * p_width;
		n = 0;
		while (c2.r + c2.i <= 256 && n < max_iter)
		{
			c.i = 2 * c.r * c.i + cxy.i;
			c.r = c2.r - c2.i + cxy.r;
			c2.r = c.r * c.r;
			c2.i = c.i * c.i;
			n++;
		}
	}
	else
	{
		t_complexl	t;
		t_complexl	t2;
		int			q;
		long double	p;

		c.r = (r_start + j * p_width);
		c.i = (i_start + i * p_height);
		n = 0;
		q = 100000;
		while ((c.r*c.r + c.i*c.i < q)&& (n < max_iter))
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
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		m = (double)n + (1.0 - log2(log2((double)((c2.r + c2.i) / (smooth == 1 ? 1 : q)))));
		int g = (int)(m * 10) % 255;
		int b = (int)(m * 20) % 255;
		((__global unsigned int*)output)[gid] = b | g << 8;
		return ;
	}
	m = (long double)n + (smooth == 1 ? (1.0 - log2(log2((double)(c2.r + c2.i)))) : 0);
	((__global unsigned int*)output)[gid] = hsv_to_rgb(255.0 * m / max_iter, 255, 255 * (m < max_iter));
}
