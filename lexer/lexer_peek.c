/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_peek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:21:57 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 16:19:51 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"

static t_token	lexer_next_token(t_lexer *lexer)
{
	t_token	token;

	token = lexer_eat(lexer, "||", OP_OR);
	if (token.type == ERROR)
		token = lexer_eat(lexer, "|", OP_PIPE);
	if (token.type == ERROR)
		token = lexer_eat(lexer, "&&", OP_AND);
	if (token.type == ERROR)
		token = lexer_eat(lexer, ">>", OP_RDR_OUT_APP);
	if (token.type == ERROR)
		token = lexer_eat(lexer, ">", OP_RDR_OUT);
	if (token.type == ERROR)
		token = lexer_eat(lexer, "<<", OP_RDR_HEREDOC);
	if (token.type == ERROR)
		token = lexer_eat(lexer, "<", OP_RDR_IN);
	if (token.type == ERROR)
		token = lexer_eat(lexer, "(", LPAREN);
	if (token.type == ERROR)
		token = lexer_eat(lexer, ")", RPAREN);
	if (token.type == ERROR)
		token = lexer_eat_string(lexer);
	return (token);
}

t_token	lexer_peek(t_lexer *lexer)
{
	lexer_skip_spaces(lexer);
	if (!*lexer->input)
		return (token_init(NULL, 0, EOF_TOKEN));
	return (lexer_next_token(lexer));
}
