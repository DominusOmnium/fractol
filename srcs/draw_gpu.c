/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gpu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:32:28 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/20 15:46:48 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_kernel_args_gpu(t_cl *cl, t_view *v)
{
	int		err;
	double	i_start;
	double	r_start;
	double	p_height;
	double	p_width;

	i_start = (double)v->fract.i_start;
	r_start = (double)v->fract.r_start;
	p_width = (double)v->fract.p_width;
	p_height = (double)v->fract.p_height;
	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->output);
	err |= clSetKernelArg(cl->kernel, 1, sizeof(int), &v->fract.max_iter);
	err |= clSetKernelArg(cl->kernel, 2, sizeof(int), &v->fract.type);
	err |= clSetKernelArg(cl->kernel, 3, sizeof(int), &v->fract.smooth);
	err |= clSetKernelArg(cl->kernel, 4, sizeof(int), &v->mouse.x);
	err |= clSetKernelArg(cl->kernel, 5, sizeof(int), &v->mouse.y);
	err |= clSetKernelArg(cl->kernel, 6, sizeof(double), &i_start);
	err |= clSetKernelArg(cl->kernel, 7, sizeof(double), &r_start);
	err |= clSetKernelArg(cl->kernel, 8, sizeof(double), &p_height);
	err |= clSetKernelArg(cl->kernel, 9, sizeof(double), &p_width);
	if (err != CL_SUCCESS)
		throw_kernel("Failed to set kernel arguments", err);
}

static void	set_kernel_args_cpu(t_cl *cl, t_view *v)
{
	int		err;

	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->output);
	err |= clSetKernelArg(cl->kernel, 1, sizeof(int), &v->fract.max_iter);
	err |= clSetKernelArg(cl->kernel, 2, sizeof(int), &v->fract.type);
	err |= clSetKernelArg(cl->kernel, 3, sizeof(int), &v->fract.smooth);
	err |= clSetKernelArg(cl->kernel, 4, sizeof(int), &v->mouse.x);
	err |= clSetKernelArg(cl->kernel, 5, sizeof(int), &v->mouse.y);
	err |= clSetKernelArg(cl->kernel, 6, sizeof(long double),
												&v->fract.i_start);
	err |= clSetKernelArg(cl->kernel, 7, sizeof(long double),
												&v->fract.r_start);
	err |= clSetKernelArg(cl->kernel, 8, sizeof(long double),
												&v->fract.p_height);
	err |= clSetKernelArg(cl->kernel, 9, sizeof(long double),
												&v->fract.p_width);
	if (err != CL_SUCCESS)
		throw_kernel("Failed to set kernel arguments", err);
}

void		draw_parallel(t_view *v, int gpu)
{
	int		err;
	t_cl	*cl;

	cl = gpu ? &(v->cl_gpu) : &(v->cl_cpu);
	gpu ? set_kernel_args_gpu(cl, v) : set_kernel_args_cpu(cl, v);
	err = clGetKernelWorkGroupInfo(cl->kernel, cl->device,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Get kernel work group info error", err);
	if (((cl->global = WIDTH * HEIGHT) % cl->local) != 0)
		cl->global += cl->global % cl->local;
	err = clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
			&cl->global, &cl->local, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Enqueue commands error", err);
	clFinish(cl->commands);
	err = clEnqueueReadBuffer(cl->commands, cl->output, CL_TRUE,
			0, WIDTH * HEIGHT * 4, v->data_addr, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Read buffer error", err);
}
