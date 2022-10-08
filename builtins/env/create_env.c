/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:42:24 by mel-hous          #+#    #+#             */
/*   Updated: 2022/10/08 08:23:04 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../include/libft.h"
#include<stdlib.h>

t_env_node	*lstlast(t_env_node *lst)
{
	if (!lst)
		return (0);
	while (!(lst->next == NULL))
		lst = lst->next;
	return (lst);
}


void    add_back(t_env_node **lst, t_env_node *new)
{
	t_env_node	*p;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = lstlast(*lst);
	p->next = new;
}

t_env_node	*new_node(char *content, char *name, int len)
{
	t_env_node	*s;

	s = (t_env_node *)malloc(sizeof(t_env_node));
	if (s == NULL)
		return (NULL);
	s->content = content;
    s->name = name;
    s->len = len;
	s->next = NULL;
	return (s);
}

void    *manu(t_env_node   *var, char *s)
{
    int j;
    
    j = 0;
    while (s[j])
    {
        if (s[j] == '=')
            add_back(&var, new_node(ft_strdup(ft_substr(s, j + 1, -1)), ft_strdup(ft_substr(s, 0, j)), j));
        j++;
    }
    return(var);
}

t_env_node *create_env(char *env[])
{
    t_env_node *var;
    int i;
    int j;

    i = 0;
    j = 0;
    var = NULL;
    while (env[i])
    {
        var = manu(var, env[i]);
        i++;
    }
    return(var);
}