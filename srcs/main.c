#include <stdio.h>
#include <mlx.h>
#include <math.h>

RE_START = -2;
RE_END = 1;
IM_START = -1;
IM_END = 1;

int	mandelbrot(float c)
{
	float z = 0;
    int n = 0;
    while (fabsf(z) <= 2 && n < 3)
	{
		z = z * z + c;
		n++;
	}
    return (n);
}

int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 600, 400, "Fractol");
	int i = 0;
	int j;
	while (i < 400)
	{
		j = 0;
		while (j < 600)
		{
			float c = sqrt(i * i + j * j);
			int m = mandelbrot(c);
			int color = 255 - m * 255 / 3;
			mlx_pixel_put(mlx, win, i, j, color);
			j++;
		}
		i++;
	}
	mlx_loop(win);
}
