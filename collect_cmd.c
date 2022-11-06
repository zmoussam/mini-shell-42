/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:45:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/05 21:05:15 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_node   *collect_cmd(t_lexer *lexer)
{
    t_cmd			*elem;
	t_parser_node	*node;
	t_rdr_node		*rdrlst;
	t_token			token;
	// int i = 0;

	elem = NULL;
	rdrlst = NULL;
	token = get_token(lexer);
	if (token.type != ERROR || token.type != PIPE || token.type != END)
		elem = cmd_ccomponents(lexer, rdrlst);
	if (elem || rdrlst)
		node = node_create(&elem, rdrlst, CMD);
	else
		return (MISSMATCH);
	return (node);
}
