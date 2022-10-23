/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:53:03 by mel-hous          #+#    #+#             */
/*   Updated: 2022/10/23 17:10:52 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include<stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct s_env_node{
    char				*name;
    char				*content;
	int					len;
	struct s_env_node	*next;
}			t_env_node;

extern t_env_node *env_list;

t_env_node  *create_env(char **env);
t_env_node  *env_find(t_env_node *env, char  *s, int len);
void        print_list();
void        add_back(t_env_node **lst, t_env_node *new);
t_env_node  *new_node(char *content, char *name, int len);
void        ft_list_remove_if(t_env_node **begin_list, void *data_ref, int (*cmp)());
int         env_listsize(t_env_node *env);

#endif