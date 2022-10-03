/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:08:27 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/15 04:36:44 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "shell.h"
#include "libft.h"
#include "utils.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

t_node	*node_create(t_list **rdrlst, t_list **arglst)
{
	t_node	*node;
	char	**argv;
	int		argc;

	argc = ft_lstsize(*arglst);
	node = node_init(SIMPLE_CMD, NULL, NULL);
	argv = lst_to_strarr(*arglst);
	ft_lstclear(arglst, free);
	if (!node || !argv)
	{
		perror(SH_NAME);
		node_destroy(node);
		ft_free_strarr(argv);
		ft_lstclear(rdrlst, (t_lft_delfn)rdr_destroy);
		return (NULL);
	}
	node->rdrlst = *rdrlst;
	node->argc = argc;
	node->argv = argv;
	return (node);
}

t_node	*parse_cmd(t_lexer *lexer)
{
	t_list	*ret;
	t_list	*rdrlst;
	t_list	*arglst;

	rdrlst = NULL;
	arglst = NULL;
	ret = parse_cmd_elem(lexer, &rdrlst, &arglst);
	while (ret && ret != RULE_MISMATCH)
		ret = parse_cmd_elem(lexer, &rdrlst, &arglst);
	if (!ret)
	{
		ft_lstclear(&rdrlst, (t_lft_delfn)rdr_destroy);
		ft_lstclear(&arglst, free);
		return (NULL);
	}
	if (!rdrlst && !arglst)
		return (RULE_MISMATCH);
	return (node_create(&rdrlst, &arglst));
}
