#include "fractol.h"

__kernel void test(__global long double		*ci,
					__global long double	*cr,
					__global int			*max_iter)
{
	int gid = get_global_id(0);

	message[gid] += gid;
}





long double			mandelbrot(t_complex cxy, t_fractal f)
{
	t_complex	c;
	t_complex	c2;
	int			n;

	c.r = 0;
	c.i = 0;
	c2.r = 0;
	c2.i = 0;
	n = 0;
	while (c2.r + c2.i <= 256 && n < f.max_iter)
	{
		c.i = 2 * c.r * c.i + cxy.i;
		c.r = c2.r - c2.i + cxy.r;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	return (n + (f.smooth == 1 ? 1 - log(log2(fabsl(c2.r + c2.i))) : 0));
}
