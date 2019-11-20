/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:31:46 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/20 16:39:05 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		throw_kernel(char *errmsg, int code)
{
	ft_putendl("OpenCL: ");
	ft_putendl(errmsg);
	ft_putstr("Error code: ");
	ft_putnbr(code);
	ft_putendl(";\n");
	exit(1);
}

static void	build_kernel(t_cl *cl, int device_type)
{
	int		err;
	char	buffer[10000];

	err = clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		err = clGetProgramBuildInfo(cl->program, cl->device,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, NULL);
		if (err == CL_SUCCESS)
		{
			ft_putendl("Compiler error message :");
			ft_putendl(buffer);
			exit(0);
		}
		else
			throw_kernel("Error while retrieving compiler log", 0);
	}
	cl->kernel = (device_type == CL_DEVICE_TYPE_GPU) ?
					clCreateKernel(cl->program, "draw_fract", &err) :
					clCreateKernel(cl->program, "draw_fract_long", &err);
	if (err != CL_SUCCESS)
		throw_kernel("Kernel creation error", err);
	cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
		HEIGHT * WIDTH * 4, NULL, NULL);
}

void		init_kernel(t_cl *cl, int device_type)
{
	int		err;
	char	*source;

	cl->context = clCreateContextFromType(NULL, device_type, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Context creation error", err);
	err = clGetDeviceIDs(NULL, device_type, 1, &cl->device, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Get device error", err);
	cl->commands = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Command queue creation error", err);
	if ((source = load_cl_file("cl/draw_fract.cl")) == NULL)
		throw_kernel("Reading .cl file error", 0);
	cl->program = clCreateProgramWithSource(cl->context, 1,
										(const char **)&source, NULL, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Programm creation error", err);
	ft_memdel((void**)&source);
	build_kernel(cl, device_type);
}
