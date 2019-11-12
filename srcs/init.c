/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:01 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/12 14:46:35 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		free_all(t_view *view)
{
	ft_memdel((void**)&view);
	if (view->img != NULL)
		mlx_destroy_image(view->mlx, view->img);
	if (view->win != NULL)
		mlx_destroy_window(view->mlx, view->win);
}

void			init_fractal(t_fractal *f, char *fr)
{
	if (ft_strcmp(fr, "julia") == 0)
		f->type = fr_julia;
	else if (ft_strcmp(fr, "mandelbrot") == 0)
		f->type = fr_mandelbrot;
	f->x_start = WIDTH / -500.0;
	f->x_end = WIDTH / 500.0;
	f->y_start = HEIGHT / -500.0;
	f->y_end = HEIGHT / 500.0;
	f->max_iter = 50;
}

t_view			*init_view(void)
{
	t_view	*view;

	if ((view = ft_memalloc(sizeof(t_view))) == NULL ||
		(view->mlx = mlx_init()) == NULL ||
		(view->win = mlx_new_window(view->mlx, WIDTH, HEIGHT, "Fractol")) == NULL ||
		(view->img = mlx_new_image(view->mlx, WIDTH, HEIGHT)) == NULL ||
		(view->data_addr = (t_color*)mlx_get_data_addr(view->img, &(view->bpp),
		&(view->line_size), &(view->endian))) == NULL)
	{
		free_all(view);
		return (NULL);
	}
	return (view);
}

static int		wind_close(void *param)
{
	(void)param;
	exit(0);
}

void			setup_hooks(t_view *v)
{
	mlx_mouse_hook(v->win, &mouse_press, v);
	mlx_hook(v->win, 5, 0, &mouse_release, v);
	mlx_hook(v->win, 6, 0, &mouse_move, v);
	mlx_key_hook(v->win, &key_press, v);
	mlx_hook(v->win, 17, 0, &wind_close, v);
}
