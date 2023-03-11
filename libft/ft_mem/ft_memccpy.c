/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:28:51 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:17:52 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_p[i] = src_p[i];
		if (src_p[i] == (unsigned char)c)
			return ((void *)(dst_p + i + 1));
		i++;
	}
	return (NULL);
}
