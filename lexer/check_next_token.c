/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_next_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:20:04 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/05 16:31:27 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	check_next_token(t_lexer	lexer, int i)
{
	// t_token token;

	while (lexer.str[++i] == 32)
	lexer.str += i;
    if (!ft_strncmp(lexer.str, "<", 1))
		return (t_init(RD_IN, 1, lexer.str));
	if (!ft_strncmp(lexer.str, ">", 1))
		return (t_init(RD_OUT, 1, lexer.str));
	if (!ft_strncmp(lexer.str, "<<", 2))
		return (t_init(HERDOC, 2, lexer.str));
	if (!ft_strncmp(lexer.str, "<<", 2))
		return (t_init(RD_APP, 2, lexer.str));
	return (t_init(TRUE, 0, NULL));
}

// void fun(t_node *root)
// {
// 	if (root = NULL)
// 		return
// 	if (root->type == PIPE)
// 	{
// 		fun(root->left);
// 		fun(root->right);
// 	}
// 	else
// 		printf("root->argv = %s\n", argv);
// }