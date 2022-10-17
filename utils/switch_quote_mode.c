/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_quote_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 01:15:46 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/28 04:23:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_quote_mode	switch_quote_mode(t_quote_mode mode, char next_char)
{
	if (next_char == '\'')
	{
		if (mode == SINGLE_QUOTED)
			return (UNQUOTED);
		if (mode == UNQUOTED)
			return (SINGLE_QUOTED);
	}
	else if (next_char == '"')
	{
		if (mode == DOUBLE_QUOTED)
			return (UNQUOTED);
		if (mode == UNQUOTED)
			return (DOUBLE_QUOTED);
	}
	return (mode);
}
