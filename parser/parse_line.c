/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:38:37 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:18:01 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"

t_node	*parse_line(t_lexer *lexer)
{
	t_node	*pipeline;
	t_token	token;

	pipeline = parse_pipeline(lexer);
	if (!pipeline || pipeline == RULE_MISMATCH)
		return (pipeline);
	token = lexer_next(lexer);
	if (token.type != EOF_TOKEN)
	{
		print_syntax_error(lexer, token);
		node_tree_clear(&pipeline);
	}
	return (pipeline);
}
