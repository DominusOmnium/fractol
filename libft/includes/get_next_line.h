/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:36:55 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/24 11:39:33 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 16
# include "libft.h"

typedef struct	s_list_fds
{
	int					fd;
	char				*buff;
	struct s_list_fds	*next;
}				t_list_fds;
int				get_next_line(const int fd, char **line);
#endif
