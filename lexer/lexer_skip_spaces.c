/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_skip_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:36:59 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/22 19:51:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"

size_t	lexer_skip_spaces(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (ft_isspace(lexer->input[i]))
		i++;
	return (lexer_advance(lexer, i));
}
