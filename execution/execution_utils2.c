/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:32:18 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 00:00:15 by zmoussam         ###   ########.fr       */
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
			exit(1);
		}
		waitpid(pid, &g_lbv.exit_status, 0);
		if (v == 2)
			free(path);
		return (1);
	}
	else if (v == 1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		g_lbv.exit_status = 127 * 256;
	}
	return (0);
}

void	execution_cmd(t_parser_node *root)
{
	char	*copy;

	copy = ft_strdup(root->av[0]);
	str_tolower(copy);
	if (ft_strcmp(copy, "echo") == 0)
		echo(root);
	else if (ft_strcmp(copy, "env") == 0)
		env_cmd(root);
	else if (ft_strcmp(root->av[0], "cd") == 0)
		cd(root);
	else if (ft_strcmp(copy, "pwd") == 0)
		pwd(root);
	else if (ft_strcmp(root->av[0], "unset") == 0)
		unset(root, 1);
	else if (ft_strcmp(root->av[0], "exit") == 0)
		exit_cmd(root);
	else if (ft_strcmp(root->av[0], "export") == 0)
		export(root);
	else
		launch_executabl(root);
	free(copy);
}

void	free_path_content(char **split_content)
{
	int	i;

	i = 0;
	while (split_content[i])
		free(split_content[i++]);
	free(split_content);
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
		free(tmp_path);
		i++;
	}
	if (split_content[i] == NULL)
	{
		g_lbv.exit_status = 127 * 256;
		printf("minishell: %s: command not found\n", argv[0]);
	}
	free_path_content(split_content);
}

void	launch_executabl(t_parser_node *root)
{
	t_env_node	*path_node;
	char		**args;
	char		**env;

	env = copy_env(env_listsize(g_lbv.list), 0);
	args = (char **)malloc(sizeof(char *) * (root->ac + 1));
	if (check_path(root->av[0]))
		execute_file(root->av[0], root->av, env, 1);
	else
	{
		path_node = env_find(g_lbv.list, "PATH", 4);
		if (path_node)
			searsh_in_path(path_node->content, root->av, env, args);
		else
		{
			g_lbv.exit_status = 127 * 256;
			printf("minishell: %s: No such file or directory\n", root->av[0]);
		}
	}
	free_env(env);
	free(args);
}
