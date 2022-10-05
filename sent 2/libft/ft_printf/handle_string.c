/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
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
#include <sys/types.h>
#include <limits.h>

int	ft_printf_handle_string(int spec, int min_w, int pr, va_list *ap)
{
	char	*s;
	size_t	len;
	ssize_t	writec;

	s = va_arg(*ap, char *);
	writec = 0;
	if (!s)
		s = "(null)";
	len = ft_strnlen(s, pr);
	if (!(spec & FLAG_MINUS))
		while ((size_t)min_w-- > len)
			ft_putchar_acc(' ', &writec);
	ft_putnstr_acc(s, len, &writec);
	if (spec & FLAG_MINUS)
		while ((size_t)min_w-- > len)
			ft_putchar_acc(' ', &writec);
	return (writec);
}
