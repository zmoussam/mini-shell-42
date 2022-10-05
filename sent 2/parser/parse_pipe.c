/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:29 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 16:56:51 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "parser.h"

t_node	*parse_pipe(t_lexer *lexer)
{
	t_node	*pipeline;
	t_node	*pipe;

	if (lexer_peek(lexer).type != OP_PIPE)
		return (RULE_MISMATCH);
	lexer_next(lexer);
	pipeline = parse_pipeline(lexer);
	if (pipeline == RULE_MISMATCH)
	{
		print_syntax_error(lexer, lexer_peek(lexer));
		return (NULL);
	}
	pipe = node_init(PIPE, NULL, pipeline);
	if (pipeline && pipe)
		return (pipe);
	node_tree_clear(&pipeline);
	node_tree_clear(&pipe);
	return (NULL);
}
