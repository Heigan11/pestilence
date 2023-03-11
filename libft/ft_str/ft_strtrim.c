/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:11:29 by chilton           #+#    #+#             */
/*   Updated: 2021/04/22 21:39:52 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*new_str;
	size_t	size;

	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1);
	while (*start && ft_strchr(set, *start))
		start++;
	while (end >= s1 && ft_strchr(set, *end))
		end--;
	if (start <= end)
		size = end - start + 1;
	else
		size = 0;
	new_str = malloc((size + 1) * sizeof(char));
	if (new_str)
		ft_strlcpy(new_str, start, size + 1);
	return (new_str);
}
