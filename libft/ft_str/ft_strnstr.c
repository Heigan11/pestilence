/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:12:39 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:12:13 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (*haystack && (needle_len <= len - i) && (i < len))
	{
		if (!(ft_strncmp(haystack, needle, needle_len)))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
