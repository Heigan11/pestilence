/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:14:13 by chilton           #+#    #+#             */
/*   Updated: 2020/11/02 14:15:57 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	res;

	res = ft_strlen(src);
	i = 0;
	while (i < dstsize && dst[i])
	{
		i++;
	}
	if (i == dstsize)
		return (i + res);
	res += i;
	while (i < dstsize - 1 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	dst[i] = '\0';
	return (res);
}
