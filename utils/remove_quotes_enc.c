/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_enc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:47:17 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 18:52:58 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "utils.h"

char	*remove_quotes_enc(char *start)
{
	char	*s;
	size_t	n;

	s = start;
	n = ft_strlen(s) + 1;
	while (*s)
	{
		if (*s == ENCODED_SINGLEQ || *s == ENCODED_DOUBLEQ)
			ft_memcpy(s, s + 1, n - 1);
		else
			s++;
		n--;
	}
	return (start);
}
