/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:41:45 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 16:58:03 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "parser.h"

t_node	*parse_pipeline(t_lexer *lexer)
{
	t_node	*cmd;
	t_node	*pipe;

	cmd = parse_cmd(lexer);
	if (cmd && cmd != RULE_MISMATCH)
	{
		pipe = parse_pipe(lexer);
		if (pipe == RULE_MISMATCH)
			return (cmd);
		if (pipe)
			pipe->left = cmd;
		else
			node_tree_clear(&cmd);
		return (pipe);
	}
	return (cmd);
}
