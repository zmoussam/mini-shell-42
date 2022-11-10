/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:30:07 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/10 10:36:23 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    str_tolower(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        str[i] = ft_tolower(str[i]);
}
int	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**copy_env(void)
{
	int			i;
	char		*temp;
	int			size;
	t_env_node	*head;
	char		**env;

	i = 0;
	size = env_listsize(glb_v.list);
	env = (char **)malloc((size + 1) * sizeof(char *));
	head = glb_v.list;
	while (head && i < size)
	{
		temp = ft_strjoin(head->name, "=");
		if (ft_strcmp(head->name, "SHLVL") == 0)
			env[i] = ft_strjoin(temp, ft_itoa((ft_atoi(head->content) + 1)));
		else 
			env[i] = ft_strjoin(temp, head->content);
		free(temp);
		head = head->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	copy_argv_for_execve(char **root_argv, char **args, char *first_arg)
{
	int	j;

	j = 1;
	args[0] = first_arg;
	while (root_argv[j])
	{
		args[j] = root_argv[j];
		j++;
	}
	args[j] = NULL;
}