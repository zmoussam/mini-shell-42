/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:43 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/03 23:32:45 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsers.h"
#include "handlers.h"
#include "spec.h"
#include <stddef.h>

t_ft_printf_handler	*ft_printf_get_handler(int spec)
{
	if (spec & (SPECIFIER_D | SPECIFIER_I))
		return (ft_printf_handle_decimal);
	else if (spec & SPECIFIER_U)
		return (ft_printf_handle_unsigned);
	else if (spec & (SPECIFIER_X | SPECIFIER_UPPER_X))
		return (ft_printf_handle_hex);
	else if (spec & SPECIFIER_C)
		return (ft_printf_handle_char);
	else if (spec & SPECIFIER_S)
		return (ft_printf_handle_string);
	else if (spec & SPECIFIER_P)
		return (ft_printf_handle_pointer);
	else if (spec & SPECIFIER_PERCENT)
		return (ft_printf_handle_percent);
	return (NULL);
}
