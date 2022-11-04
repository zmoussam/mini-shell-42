/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:53:03 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/04 01:13:13 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include<stdlib.h>
# include <stdio.h>
# include <stddef.h>

typedef struct	s_env_node{
	char				*name;
	char				*content;
	int					len;
	struct s_env_node	*next;
}			t_env_list;

extern t_env_list	*g_env_list;

t_env_list	*create_env(char **env);
t_env_list	*env_find(t_env_list *env, char *s, int len);
void		print_list(void);
void		add_back(t_env_list **lst, t_env_list *new);
t_env_list	*new_node(char *content, char *name, int len);
void		ft_list_remove_if(t_env_list **begin_list, void *data_ref);
int			env_listsize(t_env_list *env);
void		delone_env(t_env_list *node);

#endif
