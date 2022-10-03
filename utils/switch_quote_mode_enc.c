/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_quote_mode_enc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:24:29 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/28 04:23:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_quote_mode	switch_quote_mode_enc(t_quote_mode mode, char next_char)
{
	if (next_char == ENCODED_SINGLEQ)
	{
		if (mode == SINGLE_QUOTED)
			return (UNQUOTED);
		if (mode == UNQUOTED)
			return (SINGLE_QUOTED);
	}
	else if (next_char == ENCODED_DOUBLEQ)
	{
		if (mode == DOUBLE_QUOTED)
			return (UNQUOTED);
		if (mode == UNQUOTED)
			return (DOUBLE_QUOTED);
	}
	return (mode);
}
