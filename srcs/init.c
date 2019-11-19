/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:01 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/19 18:03:59 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		free_all(t_view **view)
{
	if ((*view)->img != NULL)
		mlx_destroy_image((*view)->mlx, (*view)->img);
	if ((*view)->win != NULL)
		mlx_destroy_window((*view)->mlx, (*view)->win);
	ft_memdel((void**)view);
	return (0);
}

int				init_fractal(t_fractal *f, char *fr)
{
	if (ft_strcmp(fr, "julia") == 0)
		setup_julia(f);
	else if (ft_strcmp(fr, "mandelbrot") == 0)
		setup_mandelbrot(f);
	else
		return (0);
	f->max_iter = 25;
	f->smooth = true;
	return (1);
}

int				init_view(t_view **view)
{
	
	if ((*view = ft_memalloc(sizeof(t_view))) == NULL ||
	((*view)->mlx = mlx_init()) == NULL ||
	((*view)->img = mlx_new_image((*view)->mlx, WIDTH, HEIGHT)) == NULL ||
	((*view)->data_addr = (int*)mlx_get_data_addr((*view)->img, &((*view)->bpp),
	&((*view)->line_size), &((*view)->endian))) == NULL ||
	((*view)->win = mlx_new_window((*view)->mlx, WIDTH,
									HEIGHT, "Fractol")) == NULL)
		return (free_all(view));
	(*view)->mouse.is_pressed = false;
	(*view)->mouse.prev_x = -1;
	(*view)->mouse.prev_y = -1;
	(*view)->shift = false;
	return (1);
}

static int		wind_close(t_view **v)
{
	free_all(v);
	exit(0);
}

void			setup_hooks(t_view **v)
{
	mlx_mouse_hook((*v)->win, &mouse_press, *v);
	mlx_hook((*v)->win, KEY_PRESS_EVENT, 0, &key_press, *v);
	mlx_hook((*v)->win, KEY_RELESE_EVENT, 0, &key_release, *v);
	mlx_hook((*v)->win, MOUSE_RELESE_EVENT, 0, &mouse_release, *v);
	mlx_hook((*v)->win, MOUSE_MOVE_EVENT, 0, &mouse_move, *v);
	mlx_hook((*v)->win, WIND_CLOSE_EVENT, 0, &wind_close, v);
}
