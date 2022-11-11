/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:32:18 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 17:59:43 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_file(char *path, char **argv, char **env, int v)
{
	int	pid;

	if (!access(path, X_OK))
	{
		pid = fork();
		if (pid == -1)
			printf("minishell: %s\n", strerror(errno));
		else if (pid == 0)
		{
			if (execve(path, argv, env) == -1)
				printf("minishell: %s\n", strerror(errno));
			exit(0);
		}
		waitpid(pid, NULL, 0);
		if (v == 2)
			free(path);
		return (1);
	}
	else if (v == 1)
		printf("minishell: %s: %s\n", path, strerror(errno));
	return (0);
}

void	searsh_in_path(char *path_content, char **argv, char **env, char **args)
{
	char	**split_content;
	char	*tmp_path;
	char	*tmp2_path;
	int		i;

	split_content = ft_split(path_content, ':');
	i = 0;
	while (split_content[i])
	{
		tmp2_path = ft_strjoin("/", argv[0]);
		tmp_path = ft_strjoin(split_content[i], tmp2_path);
		free(tmp2_path);
		copy_argv_for_execve(argv, args, tmp_path);
		if (execute_file(tmp_path, args, env, 2))
			break ;
		else if (split_content[i + 1] == NULL)
			printf("minishell: %s: command not found\n", argv[0]);
		free(tmp_path);
		i++;
	}
	i = 0;
	while (split_content[i])
		free(split_content[i++]);
	free(split_content);
}

void	launch_executabl(t_parser_node *root)
{
	t_env_node	*path_node;
	char		**args;
	char		**env;

	env = copy_env();
	args = (char **)malloc(sizeof(char *) * (root->ac + 1));
	if (check_path(root->av[0]))
		execute_file(root->av[0], root->av, env, 1);
	else
	{
		path_node = env_find(g_lbv.list, "PATH", 4);
		if (path_node)
			searsh_in_path(path_node->content, root->av, env, args);
		else
			printf("minishell: %s: No such file or directory\n", root->av[0]);
	}
	free_env(env);
	free(args);
}
