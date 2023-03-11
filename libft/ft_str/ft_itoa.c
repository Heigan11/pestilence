/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chilton <chilton@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:50:27 by chilton           #+#    #+#             */
/*   Updated: 2021/04/23 16:40:03 by chilton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr_len(int n, char *sign, int *first_digit_ind)
{
	char	len;

	len = 0;
	if (n < 0)
	{
		*sign = -1;
		*first_digit_ind = 1;
		len++;
	}
	else
	{
		*sign = 1;
		*first_digit_ind = 0;
	}
	len++;
	n /= 10;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	sign;
	int		first_digit_ind;
	char	*new_str;

	n_len = get_nbr_len(n, &sign, &first_digit_ind);
	new_str = malloc((n_len + 1) * sizeof(char));
	if (new_str)
	{
		if (sign == -1)
			new_str[0] = '-';
		new_str[n_len] = '\0';
		n_len--;
		while (n_len >= first_digit_ind)
		{
			new_str[n_len] = n % 10 * sign + '0';
			n /= 10;
			n_len--;
		}
	}
	return (new_str);
}
