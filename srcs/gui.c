/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:03:46 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/04 12:09:02 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_fract_gui(t_view *v)
{
	char	*tmp;

	mlx_string_put(v->mlx, v->win, 5, 5, COLOR_WHITE, "Max iterations: ");
	tmp = ft_itoa(v->fract.max_iter);
	mlx_string_put(v->mlx, v->win, 200, 5, COLOR_WHITE, tmp);
	ft_memdel((void**)&tmp);
	if (v->draw_type == gpu_parallel)
		mlx_string_put(v->mlx, v->win, 5, 30, COLOR_WHITE,
											"Drawing mode: GPU parallel");
	else if (v->draw_type == cpu_parallel)
		mlx_string_put(v->mlx, v->win, 5, 30, COLOR_WHITE,
											"Drawing mode: CPU parallel");
	else if (v->draw_type == cpu)
		mlx_string_put(v->mlx, v->win, 5, 30, COLOR_WHITE,
											"Drawing mode: CPU simple");
	if (v->fract.smooth == true)
		mlx_string_put(v->mlx, v->win, 5, 55, COLOR_WHITE,
											"Color mode: smooth");
	else if (v->fract.smooth == false)
		mlx_string_put(v->mlx, v->win, 5, 55, COLOR_WHITE,
											"Color mode: simple");
	mlx_string_put(v->mlx, v->win, 5, 80, COLOR_WHITE, "Press H for help");
}

static void	draw_background(t_view *v)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		v->data_addr[i++] = COLOR_BGR_HELP;
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
}

static void	draw_help2(t_view *v)
{
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 150,
		COLOR_TEXT_DEF, "Change color:           C");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 200,
		COLOR_TEXT_DEF, "Lock/Unlock Julia:      L");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 250,
		COLOR_TEXT_DEF, "Reset:                  R");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 300,
		COLOR_TEXT_DEF, "Close programm:         ESC");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 500,
		COLOR_TEXT_DEF, "PRESS H TO CLOSE HELP");
}

void		draw_help(t_view *v)
{
	draw_background(v);
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 - 300,
		COLOR_TEXT_DEF, "Controls:");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300,
			HEIGHT / 2 - 250, COLOR_TEXT_DEF,
			"Zoom:                   mouse wheel (hold shift to fast zoom)");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 - 200,
		COLOR_TEXT_DEF, "Move:                   mouse drag");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 - 150,
		COLOR_TEXT_DEF, "Increase iterations:    +");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 - 100,
		COLOR_TEXT_DEF, "decrease iterations:    -");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 - 50,
		COLOR_TEXT_DEF, "GPU parallel drawing:   Q");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2,
		COLOR_TEXT_DEF, "CPU parallel drawing:   W");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 50,
		COLOR_TEXT_DEF, "Simple CPU drawing:     E");
	mlx_string_put(v->mlx, v->win, WIDTH / 2 - 300, HEIGHT / 2 + 100,
		COLOR_TEXT_DEF, "Change color mode:      S");
	draw_help2(v);
}
