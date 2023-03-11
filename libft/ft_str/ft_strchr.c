/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:45:26 by chilton           #+#    #+#             */
/*   Updated: 2021/04/21 21:11:53 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if (*p == (char)c)
		return (p);
	return (NULL);
}
