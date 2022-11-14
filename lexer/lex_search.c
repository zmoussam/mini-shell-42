/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:27:05 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/14 08:07:32 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	expand_all(t_lexer	*lexer, int var, int len)
{
	t_token	token;

	if (var == 2)
	{
		token = lex_wildcard(*lexer, len);
		if (token.wildcard != NULL)
		{
			token.len = len;
			return (token);
		}
	}
	if (var == 1)
	{
		token = lex_var(*lexer, len);
		if (token.type == VAR)
		{
			token.len = len;
			return (token);
		}
	}
	return (t_init(WORD, len, lexer->str));
}

t_token	word_collect(t_lexer *lexer, int var, int len)
{
	int		mode;
	char	*s;
	t_token	token;

	s = lexer->str;
	mode = 0;
	while (s[len] != '\0' && (mode != 0 || (ft_strchr(" \t\n|&()<>", s[len]))))
	{
		mode = change_mode2(mode, s[len]);
		if (s[len] == '$' && mode != 1)
			var = 1;
		if (s[len] == '*' && var == 0 && mode == 0)
			var = 2;
		len++;
	}
	if (!len)
		return (t_init(TOK, 0, lexer->str));
	if (mode != 0 && s[len] == '\0')
		return (t_init(ENDF, 0, NULL));
	token = expand_all(lexer, var, len);
	return (token);
}
