/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:29 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 23:49:41 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

t_node	*node_init(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node)
	{
		node->type = type;
		node->left = left;
		node->right = right;
		node->argv = NULL;
		node->rdrlst = NULL;
	}
	return (node);
}
