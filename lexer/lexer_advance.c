/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:39:05 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/22 19:11:48 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

size_t	lexer_advance(t_lexer *lexer, size_t n)
{
	n = ft_strnlen(lexer->input, n);
	lexer->input += n;
	lexer->pos += n;
	return (n);
}
