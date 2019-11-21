/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:47:25 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/21 16:14:30 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	return_mes(char *s, int ret)
{
	ft_putendl(s);
	return (ret);
}

int			main(int ac, char **av)
{
	t_view	*v;

	if (ac != 2)
		return (return_mes(USAGE, 0));
	if (init_view(&v) == 0)
		return (return_mes(MEM_ERROR, 0));
	if (init_fractal(&(v->fract), av[1]) == 0)
		return (return_mes(USAGE, 0));
	init_kernel(&v->cl_gpu, CL_DEVICE_TYPE_GPU);
	init_kernel(&v->cl_cpu, CL_DEVICE_TYPE_CPU);
	draw_fractal(v);
	setup_hooks(&v);
	mlx_loop(v->mlx);
}
