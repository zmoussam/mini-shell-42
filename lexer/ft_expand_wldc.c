/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_wldc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:07:17 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/09 15:36:26 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	lex_wildcard(t_lexer	lexer, int i)
{
	char			*s;
	t_wc_node		*list;

	list = NULL;
	if (lexer.prev_type.type == HERDOC)
		return (t_init(WORD, i, lexer.str));
	s = ft_substr(lexer.str, 0, i);
	if(!s)
		return(t_init(ERROR, 0, NULL));
	list = wc_ld_create(remove_q(s));
	free(s);
	return (t_wc_init(WLDC, i, list, lexer.str));
}
