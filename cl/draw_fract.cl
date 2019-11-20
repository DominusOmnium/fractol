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
		c.r = r_start + j * p_width;
		c.i = i_start + i * p_height;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
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


		while ((c2.r + c2.i < 4) && (c2.r + c2.i > -4) && (n < max_iter))
		{
			t = z;
			p = Math.Pow(Math.Pow(t.x, 2) + Math.Pow(t.y, 2), 2);
			z.x = 2 / 3 * t.x + (Math.Pow(t.x, 2) - Math.Pow(t.y, 2)) / (3 * p);
			z.y = 2 / 3 * t.y * (1 - t.x / p);
			d.x = Math.Abs(t.x - z.x);
			d.y = Math.Abs(t.y - z.y);
			n++;
		}


	}
	m = (double)n + (smooth == 1 ? (1.0 - log2(log2(c2.r + c2.i))) : 0);
	((__global unsigned int*)output)[gid] = hsv_to_rgb(255 * m / max_iter, 255, 255 * (m < max_iter));
}


public void Draw(int mx, int my)
        {
            int n;
            double p;
            Complex z, t, d = new Complex();
 
            for (int y = -my; y < my; y++)
                for (int x = -mx; x < mx; x++)
                {
                    n = 0;
                    z.x = x * 0.005;
                    z.y = y * 0.005;
                    d = z;
                    while ((Math.Pow(z.x, 2) + Math.Pow(z.y, 2) < max) && (Math.Pow(d.x, 2) + Math.Pow(d.y, 2) > min) && (n < iter))
                    {
                        t = z;
                        p = Math.Pow(Math.Pow(t.x, 2) + Math.Pow(t.y, 2), 2);
                        z.x = 2 / 3 * t.x + (Math.Pow(t.x, 2) - Math.Pow(t.y, 2)) / (3 * p);
                        z.y = 2 / 3 * t.y * (1 - t.x / p);
                        d.x = Math.Abs(t.x - z.x);
                        d.y = Math.Abs(t.y - z.y);
                        n++;
                    }
                    pen.Color = Color.FromArgb(255, (n * 9) % 255, 0, (n * 9) % 255);
                    g.DrawLine(pen, mx + x, my + y, mx + x + 1, my + y);
                }
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
		c.r = 0;
		c.i = 0;
		c2.r = 0;
		c2.i = 0;
		cxy.i = i_start + i * p_height;
		cxy.r = r_start + j * p_width;
		n = 0;
		while (c2.r + c2.i <= 256 && n < max_iter)
		{
			c.i = 4 * c.r * c.i + cxy.i;
			c.r = c2.r - c2.i + cxy.r;
			c2.r = c.r * c.r;
			c2.i = c.i * c.i;
			n++;
		}
	}
	m = (long double)n + (smooth == 1 ? (1.0 - log2(log2((double)(c2.r + c2.i)))) : 0);
	((__global unsigned int*)output)[gid] = hsv_to_rgb(255.0 * m / max_iter, 255, 255 * (m < max_iter));
}
