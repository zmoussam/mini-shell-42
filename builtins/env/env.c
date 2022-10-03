/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:42:14 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/02 18:45:04 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "env.h"

void    env_cmd(t_env_node *top, int argc)
{
    t_env_node *head;
    head = top;
    if (argc != 1)
        printf("use env with no options or arguments\n");
    else
    while (head)
    {
        printf("%s=%s\n",head->name, head->content);
        head = head->next;
    }
}