/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:03:28 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/08 03:36:28 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	token_init(const char *s, size_t len, t_token_type type)
{
	t_token	token;

	token.s = s;
	token.len = len;
	token.type = type;
	return (token);
}
