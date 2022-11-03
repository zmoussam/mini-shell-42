/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:38:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/01 08:54:49 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../../../include/libft.h"

t_env_list	*env_find(t_env_list *env, char *s, int len)
{
	if (len == -1)
		len = ft_strlen(s);
	while (env != NULL)
	{
		if (len == env->len && !ft_strncmp(env->name, s, len))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_list_remove_if(t_env_list **begin_list, void *data_ref)
{
	t_env_list	*cur;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	cur = *begin_list;
	if (ft_strcmp(cur->name, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur->name);
		free(cur->content);
		free(cur);
		ft_list_remove_if(begin_list, data_ref);
	}
	else
		ft_list_remove_if(&cur->next, data_ref);
}
