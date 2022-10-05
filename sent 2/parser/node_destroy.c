/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:35:40 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/31 23:50:29 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	node_destroy(t_node *node)
{
	if (node)
	{
		ft_free_strarr(node->argv);
		ft_lstclear(&node->rdrlst, (t_lft_delfn)rdr_destroy);
		free(node);
	}
}
