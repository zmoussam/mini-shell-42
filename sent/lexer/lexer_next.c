/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:05:48 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 15:00:24 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"

t_token	lexer_next(t_lexer *lexer)
{
	t_token	token;

	token = lexer_peek(lexer);
	lexer_advance(lexer, token.len);
	return (token);
}
