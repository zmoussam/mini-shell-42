/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:21 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 18:19:09 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include<string.h>
# include<errno.h>
# include "../../env1/env.h"
# include "../../parser.h"
# include "../../lexer/lexer.h"

void	echo(t_parser_node *root);
void	env_cmd(t_parser_node *root);
void	cd(t_parser_node *root);
void	pwd(t_parser_node *root);
void	unset(t_parser_node *root);
void	exit_cmd(t_parser_node *root);
void	export(t_parser_node *root);
void	print_sort_list(void);

#endif
