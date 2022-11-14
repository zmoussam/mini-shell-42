/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:42:24 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 21:41:42 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
	return (var);
}
