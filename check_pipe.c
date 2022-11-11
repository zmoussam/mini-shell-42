/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:55:10 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 11:48:49 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_node	*check_pipe(t_lexer *lexer)
{
	t_parser_node	*pipe_line;
	t_parser_node	*pipe;

	if (lexer->curent_type.type == PIPE)
	{
		pipe_line = ft_pipe_line(lexer);
		if (!pipe_line || pipe_line == MISSMATCH)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
			return (NULL);
		}
		else
		{
			pipe = node_create(NULL, NULL, PIPE);
			pipe->right = pipe_line;
			if (pipe)
				return (pipe);
		}
		return (pipe_line);
	}
	else
		return (MISSMATCH);
}
