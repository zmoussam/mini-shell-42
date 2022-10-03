/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:01:21 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/02 19:08:56 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "parser.h"
#include "../builtins/env/env.h"

void    echo(t_node *root);
void    env_cmd(t_env_node *top, int argc);
void    cd(t_node *root, t_env_node *env);

#endif