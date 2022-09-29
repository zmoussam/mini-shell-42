/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 01:02:10 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERS_H
# define PARSERS_H

# include <stdarg.h>

/*
 * Parses the string `*s` for format flags and sets or clears their
 * corresponding bits in the spec (some bits override others).
 * Returns the new spec.
 * Each parsed flag advances the string pointer by one.
 * `*s` may point to a '%', in which case,
 * the pointer will be advanced by one before parsing.
 */
int	ft_printf_parse_flags(const char **s, int spec);

/*
 * Parses the string `*s` for an int tha represents the precision.
 * If '*' is encountered as the first character, an int is consumed from `ap`.
 * The string pointer is advanced to skip the parsed characters.
 * If the precision is considered to be omitted, -1 is returned.
 */
int	ft_printf_parse_precision(const char **s, va_list *ap);

/*
 * Parses the string `*s` for an int tha represents the min_width.
 * If '*' is encountered as the first character, an int is consumed from `ap`.
 * The string pointer is advanced to skip the parsed characters.
 */
int	ft_printf_parse_min_width(const char **s, va_list *ap);

/*
 * Clears all specifier bits from the spec,
 * then parses the string `*s` for a format specifier,
 * and if a valid one is found, its corresponding bit is set.
 * Returns the new spec.
 * The string pointer is advanced to skip the parsed specifier.
 */
int	ft_printf_parse_specifier(const char **s, int spec);

#endif /* PARSERS_H */
