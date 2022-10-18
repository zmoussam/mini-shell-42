/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:13:41 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/18 19:26:26 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
#include "builtins.h"
#include <sys/types.h>
#include <unistd.h>

int     check_path(char *path);
void    launch_executabl(t_node *root);
void    execution_cmd(t_node *root);
void    execution(t_node *root);

#endif