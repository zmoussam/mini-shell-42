/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:24:54 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/12 14:07:13 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long int n)
{
	long int	i;

	i = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*str_cpy(char *str, long int n, int len)
{
	int		beg;

	str[len] = '\0';
	len = len - 1;
	if (n < 0)
	{
		n *= -1;
		beg = 1;
		str[0] = '-';
	}
	else
		beg = 0;
	while (len >= beg)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	long int		lln;

	lln = n;
	len = ft_len(lln);
	if (lln < 0)
		len = len + 1;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str = str_cpy(str, lln, len);
	return (str);
}
