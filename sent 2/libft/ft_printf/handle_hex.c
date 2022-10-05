/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
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

static int	digitc(unsigned int n)
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

static const char	*get_prefix(unsigned int n, int spec)
{
	if (n && spec & FLAG_HASHTAG)
	{
		if (spec & SPECIFIER_X)
			return ("0x");
		else
			return ("0X");
	}
	return ("");
}

static const char	*get_base(int spec)
{
	if (spec & SPECIFIER_UPPER_X)
		return ("0123456789ABCDEF");
	return ("0123456789abcdef");
}

int	ft_printf_handle_hex(int spec, int min_w, int pr, va_list *ap)
{
	unsigned int	n;
	const char		*prefix;
	const char		*base;
	ssize_t			writec;

	writec = 0;
	n = va_arg(*ap, unsigned int);
	base = get_base(spec);
	prefix = get_prefix(n, spec);
	if (n || pr)
		pr = ft_max(pr, digitc(n));
	if (spec & FLAG_ZERO)
		pr = ft_max(pr, min_w - ft_strlen(prefix));
	if (!(spec & FLAG_MINUS))
		while (min_w-- > pr + (int)ft_strlen(prefix))
			ft_putchar_acc(' ', &writec);
	ft_putstr_acc(prefix, &writec);
	ft_putul_acc(n, base, pr, &writec);
	if (spec & FLAG_MINUS)
		while (min_w-- > pr + (int)ft_strlen(prefix))
			ft_putchar_acc(' ', &writec);
	return (writec);
}
