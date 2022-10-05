/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:44 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "spec.h"
#include "common.h"
#include <stdarg.h>
#include <limits.h>

static char	get_sign(int spec, int n)
{
	if (n < 0)
		return ('-');
	else if (spec & FLAG_PLUS)
		return ('+');
	else if (spec & FLAG_SPACE)
		return (' ');
	else
		return (0);
}

static int	digitc(int n)
{
	int	c;

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

static void	putnbr_abs(int n, int pr, ssize_t *writec)
{
	if (!n)
	{
		while (pr-- > 0)
			ft_putchar_acc('0', writec);
	}
	else
	{
		putnbr_abs(n / 10, pr - 1, writec);
		ft_putchar_acc(ft_abs(n % 10) + 48, writec);
	}
}

int	ft_printf_handle_decimal(int spec, int min_w, int pr, va_list *ap)
{
	int		n;
	char	sign;
	ssize_t	writec;

	writec = 0;
	n = va_arg(*ap, int);
	sign = get_sign(spec, n);
	if (n || pr)
		pr = ft_max(pr, digitc(n));
	if (spec & FLAG_ZERO)
		pr = ft_max(pr, min_w - (!!sign));
	if (!(spec & FLAG_MINUS))
		while (min_w-- > pr + (!!sign))
			ft_putchar_acc(' ', &writec);
	if (sign)
		ft_putchar_acc(sign, &writec);
	putnbr_abs(n, pr, &writec);
	if (spec & FLAG_MINUS)
		while (min_w-- > pr + (!!sign))
			ft_putchar_acc(' ', &writec);
	return (writec);
}
