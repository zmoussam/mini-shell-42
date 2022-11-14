/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:42:24 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/14 02:08:11 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../lexer/lexer.h"

void	*manu(t_env_node *var, char *s)
{
	t_env_node	*new;
	char		*name;
	char		*content;
	int			j;

	j = 0;
	while (s[j])
	{
		if (s[j] == '=')
		{
			content = ft_substr(s, j + 1, -1);
			if (!content)
				return (printf("minishell:memory was not allocated!!\n"), NULL);
			name = ft_substr(s, 0, j);
			if (!name)
				return (printf("minishell:memory was not allocated!!\n"), \
				free(content), NULL);
			new = new_node(content, name, j);
			if (!new)
				return (free(name), free(content), NULL);
			add_back(&var, new);
		}
		j++;
	}
	return (var);
}

void	_shell_level(t_env_node **lst)
{
	t_env_node	*head;
	char		*shlvl;

	head = *lst;
	while (head)
	{
		if (ft_strcmp(head->name, "SHLVL") == 0)
		{
			shlvl = ft_itoa((ft_atoi(head->content) + 1));
			if (!shlvl)
				return (printf("minishell: memory was not allocated!\n"), \
				(void)0);
			free(head->content);
				head->content = shlvl;
			return ;
		}
		head = head->next;
	}
	add_back(lst, new_node(ft_strdup("1"), ft_strdup("SHLVL"), 5));
}

void	_set_pwd(t_env_node **lst)
{
	t_env_node	*head;

	head = *lst;
	while (head)
	{
		if (ft_strcmp(head->name, "PWD") == 0)
			return ;
		head = head->next;
	}
	add_back(lst, new_node(getcwd(NULL, 0), ft_strdup("PWD"), 3));
}

t_env_node	*create_env(char *env[])
{
	t_env_node	*var;
	int			i;

	i = 0;
	var = NULL;
	while (env[i])
	{
		var = manu(var, env[i]);
		if (!var)
			return (NULL);
		i++;
	}
	_set_pwd(&var);
	_shell_level(&var);
	return (var);
}
