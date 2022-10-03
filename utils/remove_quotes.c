/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:47:17 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 19:44:42 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "utils.h"
#include <stddef.h>

char	*remove_quotes(char *start)
{
	char			*s;
	size_t			n;
	t_quote_mode	mode;
	t_quote_mode	new_mode;

	s = start;
	n = ft_strlen(s) + 1;
	mode = UNQUOTED;
	while (*s)
	{
		new_mode = switch_quote_mode(mode, *s);
		if (mode != new_mode)
			ft_memcpy(s, s + 1, n - 1);
		else
			s++;
		n--;
		mode = new_mode;
	}
	return (start);
}
