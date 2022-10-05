/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match_enc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:16:50 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/28 04:23:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stdbool.h>

#define _GLOB_MATCH		(char *)-1
#define _GLOB_NOMATCH	(char *)-2

static int	ternary(bool cond, int a, int b)
{
	if (cond)
		return (a);
	return (b);
}

static bool	match_rec(const char *p, const char *s, t_quote_mode mode);

static const char	*match_star(
		const char *p,
		const char *s,
		const char *s_start,
		t_quote_mode mode
	)
{
	if (*s == '.' && (s == s_start || *(s - 1) == '/'))
		return (_GLOB_NOMATCH);
	if (*p == '\0')
	{
		if (ft_strchr(s, '/'))
			return (_GLOB_NOMATCH);
		return (_GLOB_MATCH);
	}
	if (*p == '/')
	{
		s = ft_strchr(s, '/');
		if (s == NULL)
			return (_GLOB_NOMATCH);
		return (s);
	}
	while (*s != '\0')
	{
		if (match_rec(p, s, mode))
			return (_GLOB_MATCH);
		if (*s == '/')
			break ;
		++s;
	}
	return (_GLOB_NOMATCH);
}

static bool	match_rec(const char *p, const char *s, t_quote_mode mode)
{
	const char	*s_start = s;

	while (true)
	{
		while (*p == ENCODED_SINGLEQ || *p == ENCODED_DOUBLEQ)
			mode = switch_quote_mode_enc(mode, *p++);
		if (*p == '\0')
			return (ternary(*s == '\0', true, false));
		else if (mode == UNQUOTED && *p == '*')
		{
			while (*p == ENCODED_SINGLEQ || *p == ENCODED_DOUBLEQ
				|| (mode == UNQUOTED && *p == '*'))
				mode = switch_quote_mode_enc(mode, *p++);
			s = match_star(p, s, s_start, mode);
			if (s == _GLOB_MATCH)
				return (true);
			if (s == _GLOB_NOMATCH)
				return (false);
			continue ;
		}
		else if (*p++ != *s++)
			return (false);
	}
}

bool	glob_match_enc(const char *p, const char *s)
{
	return (match_rec(p, s, UNQUOTED));
}
