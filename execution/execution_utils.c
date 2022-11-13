/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:30:07 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 21:41:02 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	str_tolower(char *str)
{
	int	i;

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

char	**copy_env(int size, int index)
{
	t_env_node	*head;
	char		*temp;
	char		**env;
	char		*shlv;

	env = (char **)malloc((size + 1) * sizeof(char *));
	head = g_lbv.list;
	while (head && index < size)
	{
		temp = ft_strjoin(head->name, "=");
		if (ft_strcmp(head->name, "SHLVL") == 0)
		{
			shlv = ft_itoa((ft_atoi(head->content) + 1));
			env[index] = ft_strjoin(temp, shlv);
			free(shlv);
		}
		else
			env[index] = ft_strjoin(temp, head->content);
		free(temp);
		head = head->next;
		index++;
	}
	env[index] = NULL;
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
