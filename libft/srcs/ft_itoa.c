/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:02:17 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 19:52:13 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		i;
	int		j;
	char	buf[12];
	char	*res;

	ft_strclr(buf);
	sign = n;
	i = 1;
	if (n == 0)
		buf[i++] = '0';
	while (n != 0)
	{
		buf[i++] = n > 0 ? n % 10 + '0' : (n % 10) * -1 + '0';
		n /= 10;
	}
	if (sign < 0)
		buf[i++] = '-';
	if ((res = ft_strnew(i - 1)) == NULL)
		return (NULL);
	j = 0;
	while (--i >= 0)
		res[j++] = buf[i];
	return (res);
}
