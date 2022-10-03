/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:44 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_printf_handle_percent(
		int spec,
		int min_width,
		int precision,
		va_list *ap
		)
{
	(void)spec;
	(void)min_width;
	(void)precision;
	(void)ap;
	return (ft_putchar_fd('%', 1));
}
