/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:39:04 by chilton           #+#    #+#             */
/*   Updated: 2020/11/07 14:24:17 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;

	new_s = malloc((len + 1) * sizeof(char));
	if (new_s)
	{
		s += start;
		ft_strlcpy(new_s, s, len + 1);
	}
	return (new_s);
}
