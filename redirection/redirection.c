/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:42 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 23:22:10 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../execution/execution.h"
#include <fcntl.h>

void	redirection(t_parser_node *node)
{
	t_out_in_file	in_out_file;

	in_out_file.output_file = 1;
	in_out_file.input_file = 0;
	if (node->rdrlst->type == HERDOC)
		herdoc_(node, node->rdrlst, &in_out_file, 1);
	else if (node->rdrlst->type == RD_OUT || node->rdrlst->type == RD_APP)
		rdr_output(node, node->rdrlst, &in_out_file, 1);
	else if (node->rdrlst->type == RD_IN)
		rdr_input(node, node->rdrlst, &in_out_file, 1);
}
