/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:50:12 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/10 19:15:01 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include<string.h>
#include<errno.h>
#include "../parser.h"
void    *redirect_input(t_parser_node *node, t_rdr_node *rdrlst, int v, int *input_file);
void    *redirect_output(t_parser_node *node, t_rdr_node *rdrlst, int v, int *out_put_file);
void       redirection(t_parser_node *node);

#endif