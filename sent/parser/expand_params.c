/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:47:52 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 19:19:08 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "env.h"
#include "libft.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define NO_EXPANSION	((char *)-1)

static char	*expand_exit_code(char **sp)
{
	if (ft_strncmp(*sp, "$?", 2))
		return (NO_EXPANSION);
	*sp += 2;
	return (ft_itoa(g_sh_state.exit_status));
}

static char	*expand_env(char **sp)
{
	char	*s;
	size_t	i;
	char	*value;

	s = *sp;
	if (s[0] != '$' || (!ft_isalpha(s[1]) && s[1] != '_'))
		return (NO_EXPANSION);
	s++;
	i = 1;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	*sp = s + i;
	value = sh_getenvn(s, i);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*append_char(char *s, char c)
{
	const char	char_s[2] = {c, '\0'};
	char		*joined;

	joined = ft_strjoin(s, char_s);
	free(s);
	return (joined);
}

static char	*append_expansion(char *s, char *exp)
{
	char	*joined;

	joined = NULL;
	if (exp)
		joined = ft_strjoin(s, exp);
	free(s);
	free(exp);
	return (joined);
}

char	*expand_params(char *s)
{
	t_quote_mode	mode;
	char			*ret;
	char			*exp;

	mode = UNQUOTED;
	ret = ft_strdup("");
	while (ret && *s)
	{
		mode = switch_quote_mode_enc(mode, *s);
		exp = NO_EXPANSION;
		if (mode != SINGLE_QUOTED)
		{
			exp = expand_exit_code(&s);
			if (exp == NO_EXPANSION)
				exp = expand_env(&s);
		}
		if (exp == NO_EXPANSION)
			ret = append_char(ret, *s++);
		else
			ret = append_expansion(ret, exp);
	}
	if (!ret)
		perror(SH_NAME);
	return (ret);
}
