/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:38:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 19:01:44 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../lexer/lexer.h"

t_env_node	*env_find(t_env_node *env, char	*s, int len)
{
	t_env_node	*node;

	if (len == -1)
		len = ft_strlen(s);
	while (env)
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

char	*env_find2(t_env_node *env, char *s, int len)
{
	t_env_node	*node;

	if (len == -1)
		len = ft_strlen(s);
	while (env)
	{
		if (len == env->len && !ft_strncmp(env->name, s, len))
		{
			node = env;
			return (node->content);
		}
		env = env->next;
	}
	return (NULL);
}

void	print_list(void)
{
	t_env_node	*head;

	head = g_lbv.list;
	while (head)
	{
		if (head->content[0] != '\0')
			printf("%s=%s\n", head->name, head->content);
		head = head->next;
	}
}

void	ft_list_remove_if(t_env_node **begin_list, void *data_ref)
{
	t_env_node	*cur;

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

int	env_listsize(t_env_node *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
