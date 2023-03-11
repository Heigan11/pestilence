/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:24:23 by chilton           #+#    #+#             */
/*   Updated: 2021/04/22 20:51:45 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	char	sign;
	int		i;

	sign = 1;
	if (n < 0)
		sign = -1;
	i = 0;
	str[i++] = n % 10 * sign + '0';
	n /= 10;
	while (n)
	{
		str[i++] = n % 10 * sign + '0';
		n /= 10;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	reverse(str);
	write(fd, str, ft_strlen(str));
}
