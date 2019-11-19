#include "includes/def_values.h"

static int hsv_to_rgb(int h, int s, int v)
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

    p = (v * (255 - s)) / 256;
    q = (v * (255 - ((s * remainder) / 256))) / 256;
    t = (v * (255 - ((s * (255 - remainder)) / 256))) / 256;
	if (region == 0)
		return (p + t * 256 + v * 65536);
	if (region == 1)
		return (p + v * 256 + q * 65536);
	if (region == 2)
		return (t + v * 256 + p * 65536);
	if (region == 3)
		return (v + q * 256 + p * 65536);
	if (region == 4)
		return (v + p * 256 + t * 65536);
	return (q + p * 256 + v * 65536);
}

__kernel void test(	__global char	*output,
					int				max_iter,
					int				fr_type,
					double			i_start,
					double			r_start,
					double			p_height,
					double			p_width)
{
	int gid = get_global_id(0);

	if (gid < 0 || gid >= WIDTH * HEIGHT)
		return ;

	int i = gid / HEIGHT;
	int j = gid % WIDTH;

	double ci, cr, c2i, c2r, c3i, c3r;
	int			n;


	cr = 0;
	ci = 0;
	c2r = 0;
	c2i = 0;
	c3i = i_start + i * p_height;
	c3r = r_start + j * p_width;
	n = 0;
	while (c2r + c2i <= 256 && n < max_iter)
	{
		ci = 2 * cr * ci + c3i;
		cr = c2r - c2i + c3r;
		c2r = cr * cr;
		c2i = ci * ci;
		n++;
	}
	double m = (double)n + 1.0 - log(log2(fabs(c2r + c2i)));
	((__global unsigned int*)output)[gid] = hsv_to_rgb(255.0 * n / max_iter, 255, 255 * (n < max_iter))/* n == max_iter ? 0 : 255 + (f.smooth == 1 ? 1 - log(log2(fabsl(c2r + c2i))) : 0)*/;
}
