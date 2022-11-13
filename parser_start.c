/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:27:32 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/12 20:21:27 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_node	*parse(char *input)
{
	t_parser_node	*ast;
	t_lexer			*lexer;

	lexer = lex_init(quote_def(input));
	ast = parse_input(lexer);
	if (!ast || ast == MISSMATCH)
	{
		g_lbv.exit_status = 258 * 256;
		free(lexer);
		return (NULL);
	}
	free(lexer);
	return (ast);
}
