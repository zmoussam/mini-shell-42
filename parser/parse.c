/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:14:54 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:22:08 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"
#include "utils.h"
#include <stdlib.h>

t_node	*parse(char *line)
{
	t_lexer	lexer;
	t_node	*tree;

	line = expand_params(encode_quotes(line));
	lexer = lexer_init(line);
	tree = parse_line(&lexer);
	free(line);
	if (!tree || tree == RULE_MISMATCH)
		return (NULL);
	return (tree);
}
