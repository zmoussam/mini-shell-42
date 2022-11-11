/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:30:20 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 13:08:45 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_node	*ft_pipe_line(t_lexer *lexer)
{
	t_parser_node	*cmd;
	t_parser_node	*pipe;

	cmd = collect_cmd(lexer);
	if (cmd && cmd != MISSMATCH)
	{
		pipe = check_pipe(lexer);
		if (pipe == MISSMATCH)
			return (cmd);
		if (pipe)
			pipe->left = cmd;
		else
			node_del(&cmd);
		return (pipe);
	}
	return (cmd);
}
