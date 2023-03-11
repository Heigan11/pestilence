/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:44:55 by chilton           #+#    #+#             */
/*   Updated: 2020/11/07 14:23:14 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr)
	{
		i = 0;
		while (i < len + 1)
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	return (ptr);
}
