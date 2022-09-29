/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:19:05 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 14:44:00 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"

t_token	lexer_eat(t_lexer *lexer, const char *s, t_token_type type)
{
	size_t	len;

	len = ft_strlen(s);
	if (ft_strncmp(lexer->input, s, len))
	{
		lexer->errno = LEXER_ETOK;
		return (token_init(NULL, 0, ERROR));
	}
	return (token_init(lexer->input, len, type));
}
