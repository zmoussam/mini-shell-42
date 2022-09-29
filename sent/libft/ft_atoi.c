/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:53 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/18 01:12:20 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <errno.h>

int	ft_atoi(const char *str)
{
	int	result;
	int	digit;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		digit = (*(str++) - 48);
		if (sign == 1 && (INT_MAX - digit) / 10 < result)
			return (errno = ERANGE, INT_MAX);
		if (sign == -1 && (INT_MIN + digit) / 10 > result)
			return (errno = ERANGE, INT_MIN);
		result = result * 10 + digit * sign;
	}
	return (result);
}
