/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:43 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/03 23:32:45 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spec.h"
#include "common.h"
#include <stdarg.h>
#include <sys/types.h>

int	ft_printf_handle_char(int spec, int min_w, int pr, va_list *ap)
{
	char	c;
	ssize_t	writec;

	(void)pr;
	c = va_arg(*ap, int);
	writec = 0;
	if (!(spec & FLAG_MINUS))
		while (min_w-- > 1)
			ft_putchar_acc(' ', &writec);
	ft_putchar_acc(c, &writec);
	if (spec & FLAG_MINUS)
		while (min_w-- > 1)
			ft_putchar_acc(' ', &writec);
	return (writec);
}
