/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:41:49 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 08:48:10 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	get_next_token(t_lexer	*lexer)
{
	t_token	token;
	int		i;

	i = 0;
	lexer->prev_type = lexer->curent_type;
	token = get_token(lexer);
	lexer->str += token.len;
	lexer->curent_type = token;
	while (lexer->str[i] && lexer->str[i] == 32)
		i++;
	lexer->str += i;
	return (token);
}
