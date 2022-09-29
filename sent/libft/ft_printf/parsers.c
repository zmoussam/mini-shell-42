/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsers.h"
#include "spec.h"
#include <stdarg.h>

int	ft_printf_parse_flags(const char **s, int spec)
{
	if (**s == '%')
		(*s)++;
	while (**s)
	{
		if (**s == '#')
			spec |= FLAG_HASHTAG;
		else if (**s == '0')
			!(spec & FLAG_MINUS) && (spec |= FLAG_ZERO);
		else if (**s == '-')
			spec = (spec & ~FLAG_ZERO) | FLAG_MINUS;
		else if (**s == ' ')
			!(spec & FLAG_PLUS) && (spec |= FLAG_SPACE);
		else if (**s == '+')
			spec = (spec & ~FLAG_SPACE) | FLAG_PLUS;
		else
			break ;
		(*s)++;
	}
	return (spec);
}

int	ft_printf_parse_precision(const char **s, va_list *ap)
{
	int	value;

	if (**s != '.')
		return (-1);
	(*s)++;
	if (**s == '*')
	{
		value = va_arg(*ap, int);
		(*s)++;
	}
	else
	{
		if (!ft_isdigit(**s))
			return (0);
		value = ft_atoi(*s);
		while (ft_isdigit(**s))
			(*s)++;
	}
	if (value < 0)
		return (-1);
	return (value);
}

int	ft_printf_parse_min_width(const char **s, va_list *ap)
{
	int	value;

	if (**s == '*')
	{
		value = va_arg(*ap, int);
		(*s)++;
	}
	else
	{
		if (!ft_isdigit(**s))
			return (0);
		value = ft_atoi(*s);
		while (ft_isdigit(**s))
			(*s)++;
	}
	return (value);
}

int	ft_printf_parse_specifier(const char **s, int spec)
{
	spec &= ~SPECIFIER_MASK;
	if (**s == 'd')
		spec |= SPECIFIER_D;
	else if (**s == 'i')
		spec |= SPECIFIER_I;
	else if (**s == 'u')
		spec |= SPECIFIER_U;
	else if (**s == 'x')
		spec |= SPECIFIER_X;
	else if (**s == 'X')
		spec |= SPECIFIER_UPPER_X;
	else if (**s == 'c')
		spec |= SPECIFIER_C;
	else if (**s == 's')
		spec |= SPECIFIER_S;
	else if (**s == 'p')
		spec |= SPECIFIER_P;
	else if (**s == '%')
		spec |= SPECIFIER_PERCENT;
	else
		return (spec);
	(*s)++;
	return (spec);
}
