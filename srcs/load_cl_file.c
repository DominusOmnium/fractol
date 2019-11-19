/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cl_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:37:44 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/19 19:57:03 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	read_cl_file(char *fname, char **cl)
{
	int		fd;
	char	*line;
	char	*tmp;
	
	if ((fd = open(fname, O_RDONLY)) == -1/* || read(fd, NULL, 0) == -1*/)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		if ((tmp = ft_strjoin2(*cl, "\n", line)) == NULL)
			return (0);
		ft_memdel((void**)cl);
		ft_memdel((void**)&line);
		*cl = tmp;
	}
	close(fd);
	tmp = ft_strjoin(*cl, "\n");
	ft_memdel((void**)cl);
	*cl = tmp;
	return (1);
}

char		*load_cl_file(char *fname)
{
	char	*cl;

	if ((cl = ft_strdup("#define FROM_KERNEL\n")) == NULL)
		return (NULL);
	if (read_cl_file(fname, &cl) == 0)
		return (NULL);
	return (cl);
}


static void	throw_kernel(char *errmsg)
{
	printf("OpenCL: %s;\n", errmsg);
	exit(1);
}

void		init_kernel(t_cl *cl)
{
	int		err;
	char	*source;
	size_t	pl;
	
	cl->context = clCreateContextFromType(NULL, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Context error");
	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &cl->device, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Device error");
	cl->commands = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Commands error");
	source = load_cl_file("cl/test.cl");
	pl = ft_strlen(source);
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)&source, &pl, &err);
	if (err != CL_SUCCESS)
		throw_kernel("Programm error");
	err = clBuildProgram(cl->program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		char buffer[10000];
		size_t len;
		err = clGetProgramBuildInfo(cl->program, cl->device,
				CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
		if (err == CL_SUCCESS)
			printf("Compiler error message :\n%s\n", buffer);
		else
		{
			printf("Error while retrieving compiler log;\n");
			printf("Try increasing buffer size to 100 000;\n");
		}
	}
	cl->kernel = clCreateKernel(cl->program, "test", &err);
	if (err != CL_SUCCESS)
		throw_kernel(ft_itoa(err));
	cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
		HEIGHT * WIDTH * 4, NULL, NULL);
}

static void	set_kernel_args(t_view *v)
{
	int		err;

	err |= clSetKernelArg(v->cl.kernel, 0, sizeof(cl_mem), &v->cl.output);
	err = clSetKernelArg(v->cl.kernel, 1, sizeof(int), &v->fract.max_iter);
	err |= clSetKernelArg(v->cl.kernel, 2, sizeof(int), &v->fract.type);
	printf("istart: %F\n", v->fract.i_start);
	err |= clSetKernelArg(v->cl.kernel, 3, sizeof(double), &(v->fract.i_start));
	printf("rstart: %F\n", v->fract.r_start);
	err |= clSetKernelArg(v->cl.kernel, 4, sizeof(double), &(v->fract.r_start));
	printf("pheight: %F\n", v->fract.p_height);
	err |= clSetKernelArg(v->cl.kernel, 5, sizeof(double), &(v->fract.p_height));
	printf("pwidth: %F\n", v->fract.p_width);
	err |= clSetKernelArg(v->cl.kernel, 6, sizeof(double), &(v->fract.p_width));
	if (err != CL_SUCCESS)
		throw_kernel("Failed to set kernel arguments");
}

static void	set_cl_global(t_cl *cl)
{
	cl->global = WIDTH * HEIGHT;
	if (cl->global % cl->local != 0)
	{
		cl->global += cl->global % cl->local;
		//throw_kernel("Error");
	}
}

void		draw_gpu_fractal(t_view *v)
{
	int		err;
	t_cl	*cl;

	cl = &(v->cl);
	set_kernel_args(v);
	err = clGetKernelWorkGroupInfo(cl->kernel, cl->device,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	set_cl_global(cl);
	err = clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
			&cl->global, NULL, 0, NULL, NULL);
	if (err)
		throw_kernel(ft_itoa(err));
	clFinish(cl->commands);
	err = clEnqueueReadBuffer(cl->commands, cl->output, CL_TRUE,
			0, WIDTH * HEIGHT * 4, v->data_addr, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		throw_kernel(ft_itoa(err));
}
