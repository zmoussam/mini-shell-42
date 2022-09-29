/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:41:07 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 15:01:22 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "shell.h"

void	lexer_perror(t_lexer lexer)
{
	if (lexer.errno == LEXER_EEOF)
		ft_putstr_fd(SH_NAME ": syntax error: unexpected end of file\n", 2);
	else if (lexer.errno == LEXER_ETOK)
	{
		ft_putstr_fd(SH_NAME, 2);
		ft_putstr_fd(": syntax error: unrecognized token at position ", 2);
		ft_putnbr_fd(lexer.pos + 1, 2);
		ft_putchar_fd('\n', 2);
	}
}
