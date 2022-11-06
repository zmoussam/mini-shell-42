/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:53:03 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/06 18:43:47 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../libft/libft.h"
# include <stddef.h>

typedef struct s_env_node{
    char				*name;
    char				*content;
	int					len;
	struct s_env_node	*next;
}			t_env_list;

t_env_list  *create_env(char **env);
t_env_list  *env_find(t_env_list *env, char  *s, int len);
t_env_list	*lstlast(t_env_list *lst);
void	    add_back(t_env_list **lst, t_env_list *new);
t_env_list	*new_node(char *content, char *name, int len);
char        *env_find2(t_env_list *env, char  *s, int len);
void        ft_list_remove_if(t_env_list **begin_list, void *data_ref);
void		delone_env(t_env_list *node);
int			env_listsize(t_env_list *env);
void		print_list(void);

#endif