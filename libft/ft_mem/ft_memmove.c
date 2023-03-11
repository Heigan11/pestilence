/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:13:02 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:15:52 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	if (!dst && !src)
		return (NULL);
	src_p = (unsigned char *)src;
	dst_p = (unsigned char *)dst;
	if (dst < src)
	{
		while (len--)
		{
			*dst_p = *src_p;
			src_p++;
			dst_p++;
		}
	}
	else if (dst > src)
	{
		while (len--)
		{
			dst_p[len] = src_p[len];
		}
	}
	return (dst);
}
