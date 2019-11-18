/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cl_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:37:44 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/18 20:47:22 by dkathlee         ###   ########.fr       */
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
	printf(2, "OpenCL: %s;\n", errmsg);
	exit(1);
}

void		draw_gpu_fractal(t_view *v)
{
	int		err;
	t_cl	*cl;

	cl = &(v->cl);
	set_kernel_args(cl, v);
	err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local), &cl->local, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Failed to retrieve kernel work group info");
	set_cl_global(cl);
	err = clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
			&cl->global, &cl->local, 0, NULL, NULL);
	if (err)
		throw_kernel("Failed to execute kernel !");
	clFinish(cl->commands);
	err = clEnqueueReadBuffer(cl->commands, cl->output, CL_TRUE,
			0, WIDTH * HEIGHT * 4, v->data_addr, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		throw_kernel("Failed to read output array");
}
