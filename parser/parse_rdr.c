/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rdr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:14:00 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/08 01:07:21 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "shell.h"
#include <stdio.h>

static int	get_rdr_type(t_token op)
{
	if (op.type == OP_RDR_IN)
		return (RDR_IN);
	else if (op.type == OP_RDR_OUT)
		return (RDR_OUT);
	else if (op.type == OP_RDR_OUT_APP)
		return (RDR_OUT_APP);
	else if (op.type == OP_RDR_HEREDOC)
		return (RDR_HEREDOC);
	else
		return (-1);
}

static t_list	*add_rdr(t_rdr_type type, t_token str, t_list **rdrlst)
{
	t_rdr	*rdr;
	t_list	*new;

	rdr = rdr_init(type, str);
	if (!rdr)
		return (NULL);
	new = ft_lstnew(rdr);
	if (!new)
	{
		perror(SH_NAME);
		rdr_destroy(rdr);
		return (NULL);
	}
	ft_lstadd_back(rdrlst, new);
	return (new);
}

t_list	*parse_rdr(t_lexer *lexer, t_list **rdrlst)
{
	t_token	op;
	t_token	str;

	op = lexer_peek(lexer);
	if (get_rdr_type(op) == -1)
		return (RULE_MISMATCH);
	lexer_next(lexer);
	str = lexer_next(lexer);
	if (str.type != STRING)
	{
		print_syntax_error(lexer, str);
		return (NULL);
	}
	return (add_rdr(get_rdr_type(op), str, rdrlst));
}
