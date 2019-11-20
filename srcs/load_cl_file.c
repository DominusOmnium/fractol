/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cl_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:37:44 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/20 14:16:33 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	read_cl_file(char *fname, char **cl)
{
	int		fd;
	char	*line;
	char	*tmp;

	if ((fd = open(fname, O_RDONLY)) == -1)
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
