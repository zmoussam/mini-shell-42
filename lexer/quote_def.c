/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:49:49 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 10:03:08 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"

char	*quote_def(char	*str)
{
	char	*s;
	int		mode;

	s = str;
	mode = 0;
	while (*s)
	{
		mode = change_mode(mode, *s);
		if (*s == 34 && (mode == 2 || mode == 0))
			*s = DEF_DOUBEL_Q;
		else if (*s == 39 && (mode == 1 || mode == 0))
			*s = DEF_SINGEL_Q;
		s++;
	}
	return (str);
}
