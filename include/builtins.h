/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:21 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/30 09:26:43 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "parser.h"
#include "../execution/builtins/env/env.h"
#include<string.h>
#include<errno.h>

void    echo(t_node *root);
void    env_cmd(int argc);
void    cd(t_node *root);
void	pwd(t_node *root);
void 	unset(t_node *root);
void    exit_cmd();
void	export(t_node *root);
void	print_sort_list();

#endif