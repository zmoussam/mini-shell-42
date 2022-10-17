/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tree_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:46:30 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 16:36:44 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	node_tree_clear(t_node **tree)
{
	t_node	*node;

	node = *tree;
	if (node)
	{
		node_tree_clear(&node->left);
		node_tree_clear(&node->right);
		node_destroy(node);
		*tree = NULL;
	}
}
