/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_components.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:40:53 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/10 16:34:07 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd *cmd_ccomponents(t_lexer *lexer, t_rdr_node **rdr)
{
	t_token token;
	t_cmd *cmd;
	t_rdr_node *tmp;

	cmd = NULL;
	token = t_init(CHAR_NULL,0, NULL);
	while (token.type != END && token.type != ERROR &&
			token.type != PIPE && token.type != TOK && token.type != ENDF)
	{
		token = get_next_token(lexer);
		if(*rdr == MISSMATCH)
			break;
		else if (token.type == WORD)
			cmd_addback(&cmd, ft_new_cmd(ft_substr(token.pos, 0, token.len), NULL));
		else if (token.type == VAR)
			cmd_addback(&cmd, ft_new_cmd(token.pos, NULL));
		else if (token.type == WLDC)
			cmd_addback(&cmd, ft_new_cmd(token.pos, &token.wildcard));
		else if (token.type == RD_APP || token.type == RD_IN ||
				 token.type == RD_OUT || token.type == HERDOC)
		{
			tmp = collect_rdr(lexer, *rdr, token);
			if (tmp == MISSMATCH)
			{
				if (rdr)
					rdr_clear(rdr);
				else
					*rdr = MISSMATCH;
			}
			rdr_addback(rdr, tmp);
		}
	}
	return (cmd);
}
