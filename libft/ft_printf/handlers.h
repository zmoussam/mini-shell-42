/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 01:02:10 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include <stdarg.h>

/*
 * An ft_printf handler is a function that receives
 * the parsed spec, min-width, precision and a variadic arguments list,
 * consumes an argument from it,
 * converts it to the corresponding representation,
 * writes it to stdout,
 * then returns the number of characters written, or -1 on failure.
 * If the precision is considered to be omitted, its value is -1.
 */
typedef int	t_ft_printf_handler(
		int spec,
		int min_width,
		int precision,
		va_list *ap
		);

/*
 * Returns the corresponding handler for the provided `spec`,
 * or NULL if there's none.
 */
t_ft_printf_handler	*ft_printf_get_handler(int spec);

int					ft_printf_handle_decimal(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_unsigned(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_hex(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_char(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_string(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_pointer(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

int					ft_printf_handle_percent(
						int spec,
						int min_width,
						int precision,
						va_list *ap
						);

#endif /* HANDLERS_H */
