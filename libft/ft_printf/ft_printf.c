/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:36 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "spec.h"
#include "parsers.h"
#include "handlers.h"
#include "common.h"
#include <stdarg.h>
#include <sys/types.h>

static void	put_literal(const char **format, ssize_t *writec)
{
	ft_putnstr_acc(*format, ft_strcspn(*format, "%"), writec);
	*format += ft_strcspn(*format, "%");
}

static ssize_t	put_converted(int spec, int min_w, int pr, va_list *ap)
{
	t_ft_printf_handler	*handler;

	handler = ft_printf_get_handler(spec);
	if (!handler)
		return (-1);
	return (handler(spec, min_w, pr, ap));
}

static int	ft_vaprintf(const char *format, va_list *ap)
{
	int		spec;
	int		min_w;
	int		pr;
	ssize_t	writec;

	writec = 0;
	put_literal(&format, &writec);
	while (*format && writec != -1)
	{
		spec = ft_printf_parse_flags(&format, 0);
		min_w = ft_printf_parse_min_width(&format, ap);
		if (min_w < 0)
			spec = (spec & ~FLAG_ZERO) | FLAG_MINUS;
		min_w = ft_abs(min_w);
		pr = ft_printf_parse_precision(&format, ap);
		if (pr != -1)
			spec &= ~FLAG_ZERO;
		spec = ft_printf_parse_specifier(&format, spec);
		ft_acc_writec(put_converted(spec, min_w, pr, ap), &writec);
		put_literal(&format, &writec);
	}
	return (writec);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		writec;

	va_start(ap, format);
	writec = ft_vaprintf(format, &ap);
	va_end(ap);
	return (writec);
}
