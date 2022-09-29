/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:32:43 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 14:47:57 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	lexer_init(const char *input)
{
	t_lexer	lexer;

	lexer.full_input = input;
	lexer.input = input;
	lexer.pos = 0;
	lexer.errno = 0;
	return (lexer);
}
