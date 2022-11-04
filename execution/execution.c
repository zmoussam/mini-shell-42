/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/04 00:52:43 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/execution.h"
#include<string.h>
#include <sys/errno.h>

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
	t_env_list	*head;
	char		**env;

	i = 0;
	size = env_listsize(g_env_list);
	env = (char **)malloc(size * sizeof(char *) + 1);
	head = g_env_list;
	while (head && i < size)
	{
		temp = ft_strjoin(head->name, "=");
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

int	execute_file(char *path, char **argv, char **env, int v)
{
	int	pid;

	if (!access(path, X_OK))
	{
		pid = fork();
		if (pid == -1)
			printf("minishell: %s\n", strerror(errno));
		else if (pid == 0)
			if (execve(path, argv, env) == -1)
				printf("minishell: %s\n", strerror(errno));
		waitpid(pid, NULL, 0);
		if (v == 2)
			free(path);
		return (1);
	}
	else if (v == 1)
		printf("minishell: %s: %s\n", path, strerror(errno));
	return (0);
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

void	searsh_in_path(char *path_content, char **argv, char **env, char **args)
{
	char	**split_content;
	char	*tmp_path;
	char	*tmp2_path;
	int		i;

	split_content = ft_split(path_content, ":");
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

void	launch_executabl(t_node *root)
{
	t_env_list	*path_node;
	char		**args;
	char		**env;

	env = copy_env();
	args = (char **)malloc(sizeof(char *) * root->argc + 1);
	if (check_path(root->argv[0]))
		execute_file(root->argv[0], root->argv, env, 1);
	else
	{
		path_node = env_find(g_env_list, "PATH", 4);
		if (path_node)
			searsh_in_path(path_node->content, root->argv, env, args);
		else
			printf("minishell: %s: No such file or directory\n", root->argv[0]);
	}
	free_env(env);
	free(args);
}

void	execution_cmd(t_node *root)
{
	char	*copy;

	copy = ft_strdup(root->argv[0]);
	ft_strtolower(copy);
	if (ft_strcmp(copy, "echo") == 0)
		echo(root);
	else if (ft_strcmp(copy, "env") == 0)
		env_cmd(root->argc);
	else if (ft_strcmp(root->argv[0], "cd") == 0)
		cd(root);
	else if (ft_strcmp(copy, "pwd") == 0)
		pwd(root);
	else if (ft_strcmp(root->argv[0], "unset") == 0)
		unset(root);
	else if (ft_strcmp(root->argv[0], "exit") == 0)
		exit_cmd();
	else if (ft_strcmp(root->argv[0], "export") == 0)
		export(root);
	else
		launch_executabl(root);
	free(copy);
}

void	execute_left(int *fd, t_node *left)
{
	close(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execution(left);
	exit(0);
}

void	execute_right(int *fd, t_node *right)
{
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execution(right);
	exit(0);
}

void	execution(t_node *root)
{
	int	pid;
	int	fd[2];

	if (root == NULL)
		return ;
	if (root->type == PIPE)
	{
		if (pipe(fd) == -1)
			return ;
		pid = fork();
		if (pid == 0)
			execute_left(fd, root->left);
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
			execute_right(fd, root->right);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
		execution_cmd(root);
}
