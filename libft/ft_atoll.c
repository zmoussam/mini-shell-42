/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:17:09 by syakoubi          #+#    #+#             */
/*   Updated: 2022/10/02 17:26:02 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <errno.h>

long long	ft_atoll(const char *str)
{
	long long	result;
	int			digit;
	int			sign;

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
		if (sign == 1 && (LLONG_MAX - digit) / 10 < result)
			return (errno = ERANGE, LLONG_MAX);
		if (sign == -1 && (LLONG_MIN + digit) / 10 > result)
			return (errno = ERANGE, LLONG_MIN);
		result = result * 10 + digit * sign;
	}
	return (result);
}
