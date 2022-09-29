/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_eat_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:53:03 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:22:40 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"
#include "utils.h"

t_token	lexer_eat_string(t_lexer *lexer)
{
	size_t		len;
	const char	*s;
	int			mode;

	mode = UNQUOTED;
	len = 0;
	s = lexer->input;
	while (*s && (mode != UNQUOTED || !ft_strchr(LEXER_METACHARS, *s)))
	{
		mode = switch_quote_mode_enc(mode, *s);
		len++;
		s++;
	}
	if (!len)
	{
		lexer->errno = LEXER_ETOK;
		return (token_init(NULL, 0, ERROR));
	}
	if (mode != UNQUOTED)
	{
		lexer->errno = LEXER_EEOF;
		return (token_init(NULL, 0, ERROR));
	}
	return (token_init(lexer->input, len, STRING));
}
