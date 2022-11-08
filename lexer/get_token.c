/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:32:06 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/08 09:58:39 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token	get_token(t_lexer	*lexer)
{
	t_token	token;

	while (lexer->str && *lexer->str == 32)
		lexer->str++;
	if(lexer->str[0] == '\0')
		return (t_init(END, 0, NULL));
	if (!ft_strncmp(lexer->str, "|", 1))
		return (t_init(PIPE, 1, lexer->str));
	if (!ft_strncmp(lexer->str, "<<", 2))
		return (t_init(HERDOC, 2, lexer->str));
	if (!ft_strncmp(lexer->str, ">>", 2))
		return (t_init(RD_APP, 2, lexer->str));
	if (!ft_strncmp(lexer->str, "<", 1))
		return (t_init(RD_IN, 1, lexer->str));
	if (!ft_strncmp(lexer->str, ">", 1))
		return (t_init(RD_OUT, 1, lexer->str));
	token = word_collect(lexer);
	return (token);
}
