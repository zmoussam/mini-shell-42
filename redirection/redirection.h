/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:50:12 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 23:25:40 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include<string.h>
# include<errno.h>
# include "../parser.h"
# include "../execution/execution.h"
# include <fcntl.h>

typedef struct s_out_in_file{
	int	input_file;
	int	output_file;
}	t_out_in_file;

void	*rdr_input(t_parser_node *n, t_rdr_node *l, t_out_in_file *file, int v);
void	*rdr_output(t_parser_node *n, t_rdr_node *l, \
		t_out_in_file *file, int v);
void	*herdoc_(t_parser_node *n, t_rdr_node *l, t_out_in_file *file, int v);
char	*get_herdoc_file(t_rdr_node *rdrlst);
void	redirection(t_parser_node *node);

#endif
