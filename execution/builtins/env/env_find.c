/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:38:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/10/28 18:46:25 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../../include/libft.h"

t_env_node *env_find(t_env_node *env, char  *s, int len)
{
    t_env_node *node;
    
    if (len == -1)
        len = ft_strlen(s);
    while (env != NULL)
    {
        if (len == env->len && !ft_strncmp(env->name, s, len))
        {
            node = env;
            return (node);
        }
        env = env->next;
    }
    return (NULL);
}

void ft_list_remove_if(t_env_node **begin_list, void *data_ref, int (*cmp)())
{
	if (*begin_list == NULL || begin_list == NULL)
		return ;
	t_env_node *cur = *begin_list;

	if (cmp(cur->name , data_ref) == 0)
	{
		*begin_list = cur->next;
        free(cur->name);
        free(cur->content);
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
    else
        ft_list_remove_if(&cur->next, data_ref, cmp);
}
