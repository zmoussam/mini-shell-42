/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 20:58:43 by zmoussam         ###   ########.fr       */
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

void	launch_executabl(t_node *root)
{
	int		pid;
	int		i;
	char	**path_content;
	char	*tmp_path;
	char	*tmp2_path;
	char	**args;
	char	**env;

	env = copy_env();
	args = (char **)malloc(sizeof(char *) * root->argc + 1);
	if (check_path(root->argv[0]))
	{
		if (!access(root->argv[0], X_OK))
		{
			pid = fork();
			if (pid == -1)
				printf("%s\n", strerror(errno));
			else if (pid == 0)
			{
				if (execve(root->argv[0], root->argv, env) == -1)
					printf("%s\n", strerror(errno));
			}
			waitpid(pid, NULL, 0);
		}
		else
			printf("%s\n", strerror(errno));
	}
	else
	{
		if (env_find(g_env_list, "PATH", 4))
		{
			path_content = \
				ft_split(env_find(g_env_list, "PATH", 4)->content, ":");
			i = 0;
			while (path_content[i])
			{
				tmp2_path = ft_strjoin("/", root->argv[0]);
				tmp_path = ft_strjoin(path_content[i], tmp2_path);
				free(tmp2_path);
				if (!access(tmp_path, X_OK))
				{
					pid = fork();
					if (pid == -1)
						printf("%s\n", strerror(errno));
					if (pid == 0)
					{
						args[0] = tmp_path;
						i = 1;
						while (root->argv[i])
						{
							args[i] = root->argv[i];
							i++;
						}
						args[i] = NULL;
						if (execve(tmp_path, args, env) == -1)
						{
							printf("%s\n", strerror(errno));
						}
					}
					else
						waitpid(pid, NULL, 0);
				}
				free(tmp_path);
				i++;
			}
			i = 0;
			while (path_content[i])
				free(path_content[i++]);
			free(path_content);
		}
		else
			printf("bash: %s: No such file or directory\n", root->argv[0]);
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

void	execution(t_node *root)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	if (root == NULL)
		return ;
	if (root->type == PIPE)
	{
		pid = fork();
		if (pid == 0)
		{
			close(STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execution(root->left);
			exit(0);
		}
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
		{
			close(STDIN_FILENO);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execution(root->right);
			exit(0);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		// if redc_list;
		// call redc function
		// else
        execution_cmd(root);
	}
}
