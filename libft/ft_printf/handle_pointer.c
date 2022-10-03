/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
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

static int	digitc(unsigned long n)
{
	int	c;

	c = 1;
	while (n > 15)
	{
		n /= 16;
		c++;
	}
	return (c);
}

int	ft_printf_handle_pointer(int spec, int min_w, int pr, va_list *ap)
{
	unsigned long	n;
	int				width;
	ssize_t			writec;

	(void)pr;
	writec = 0;
	n = (unsigned long)va_arg(*ap, void *);
	if (n)
		width = digitc(n) + 2;
	else
		width = 5;
	if (!(spec & FLAG_MINUS))
		while (min_w-- > width)
			ft_putchar_acc(' ', &writec);
	if (n)
	{
		ft_putstr_acc("0x", &writec);
		ft_putul_acc(n, "0123456789abcdef", 1, &writec);
	}
	else
		ft_putstr_acc("(nil)", &writec);
	if (spec & FLAG_MINUS)
		while (min_w-- > width)
			ft_putchar_acc(' ', &writec);
	return (writec);
}
