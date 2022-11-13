/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 13:05:53 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/08 14:29:19 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_node	*parse_input(t_lexer *lexer)
{
	t_parser_node	*pipeline;
	t_token			token;

	pipeline = ft_pipe_line(lexer);
	if (!pipeline || pipeline == MISSMATCH)
		return (pipeline);
	token = get_next_token(lexer);
	if (token.type != END)
	{
		print_error(token);
		node_del(&pipeline);
		return (NULL);
	}
	return (pipeline);
}
