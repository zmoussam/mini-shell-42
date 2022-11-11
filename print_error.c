/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:31:25 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 13:19:35 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error(t_token token)
{
	if (token.type == TOK)
	{
		ft_putstr_fd("minishell: syntax error: unrecognized token ", 2);
		write(2, "'", 1);
		write(2, &token.pos[0], 1);
		write(2, "'\n", 2);
	}
	if (token.type == ERROR)
	{
		ft_putstr_fd("minishell: syntax error: unexpected token ", 2);
		write(2, "'", 1);
		write(2, "|", 1);
		write(2, "'\n", 2);
	}
	if (token.type == ENDF)
		ft_putstr_fd("minishel: syntax error: unexpected end of file\n", 2);
}
