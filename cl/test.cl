#include "fractol.h"

__kernel void test(__global long double		ci,
					__global long double	cr,
					__global int			max_iter
					__global char			*output)
{
	int gid = get_global_id(0);

	t_complex	c;
	t_complex	c2;
	int			n;

	c.r = 0;
	c.i = 0;
	c2.r = 0;
	c2.i = 0;
	n = 0;
	while (c2.r + c2.i <= 256 && n < max_iter)
	{
		c.i = 2 * c.r * c.i + ci;
		c.r = c2.r - c2.i + cr;
		c2.r = c.r * c.r;
		c2.i = c.i * c.i;
		n++;
	}
	((__global unsigned int*)output)[gid] = n + (f.smooth == 1 ? 1 - log(log2(fabsl(c2.r + c2.i))) : 0);
}
