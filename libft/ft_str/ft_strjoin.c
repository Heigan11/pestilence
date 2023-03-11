/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:20:33 by chilton           #+#    #+#             */
/*   Updated: 2021/04/22 20:28:46 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	if (new_str)
	{
		ft_memcpy(new_str, s1, len1);
		ft_memcpy(new_str + len1, s2, len2 + 1);
	}
	return (new_str);
}
