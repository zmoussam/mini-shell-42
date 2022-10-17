/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "spec.h"
#include "common.h"
#include <stdarg.h>

static int	digitc(unsigned int n)
{
	int	c;

	c = 1;
	while (n > 9)
	{
		n /= 10;
		c++;
	}
	return (c);
}

int	ft_printf_handle_unsigned(int spec, int min_w, int pr, va_list *ap)
{
	unsigned int	n;
	ssize_t			writec;

	writec = 0;
	n = va_arg(*ap, unsigned int);
	if (n || pr)
		pr = ft_max(pr, digitc(n));
	if (spec & FLAG_ZERO)
		pr = ft_max(pr, min_w);
	if (!(spec & FLAG_MINUS))
		while (min_w-- > pr)
			ft_putchar_acc(' ', &writec);
	ft_putul_acc(n, "0123456789", pr, &writec);
	if (spec & FLAG_MINUS)
		while (min_w-- > pr)
			ft_putchar_acc(' ', &writec);
	return (writec);
}
