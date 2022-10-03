/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:13:02 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 19:13:55 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*encode_quotes(char *_s)
{
	char			*s;
	t_quote_mode	mode;

	s = _s;
	mode = UNQUOTED;
	while (*s)
	{
		mode = switch_quote_mode(mode, *s);
		if (*s == '"' && (mode == DOUBLE_QUOTED || mode == UNQUOTED))
			*s = ENCODED_DOUBLEQ;
		else if (*s == '\'' && (mode == SINGLE_QUOTED || mode == UNQUOTED))
			*s = ENCODED_SINGLEQ;
		s++;
	}
	return (_s);
}
