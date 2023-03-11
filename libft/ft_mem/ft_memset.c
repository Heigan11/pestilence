/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:23:59 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:15:41 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	chr;

	p = (unsigned char *)b;
	chr = (unsigned char)c;
	while (len--)
	{
		*p = chr;
		p++;
	}
	return (b);
}
