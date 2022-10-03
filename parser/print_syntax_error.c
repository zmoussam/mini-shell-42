/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:09:41 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 23:35:58 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "shell.h"

void	print_syntax_error(t_lexer *lexer, t_token token)
{
	if (token.type == EOF_TOKEN)
		ft_putstr_fd(SH_NAME ": syntax error: unexpected end of file\n", 2);
	else if (token.type == ERROR)
		lexer_perror(*lexer);
	else
	{
		ft_putstr_fd(SH_NAME ": syntax error near unexpected token ", 2);
		ft_putchar_fd('\'', 2);
		ft_putnstr_fd(token.s, token.len, 2);
		ft_putstr_fd("'\n", 2);
	}
}
