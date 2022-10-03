/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:53 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:02 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

static unsigned int	ft_digitc(int n)
{
	unsigned int	c;

	c = 1;
	if (n == INT_MIN)
		n = INT_MAX;
	n = ft_abs(n);
	while (n > 9)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;

	len = ft_digitc(n);
	if (n < 0)
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str += len;
	*str = '\0';
	while (n > 9 || n < -9)
	{
		*(--str) = ft_abs(n % 10) + 48;
		n /= 10;
	}
	*(--str) = ft_abs(n) + 48;
	if (n < 0)
		*(--str) = '-';
	return (str);
}
