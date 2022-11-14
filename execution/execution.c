/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 13:41:08 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "execution.h"
#include<string.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "../redirection/redirection.h"

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
		launch_executabl(root, env_listsize(g_lbv.list));
	free(copy);
}

void	execute_left(int *fd, t_parser_node *left)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execution(left);
	exit(127);
}

void	execute_right(int *fd, t_parser_node *right)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execution(right);
	exit(0);
}

void	pipe_fork(t_parser_node *root)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		execute_left(fd, root->left);
	pid = fork();
	if (pid == 0)
		execute_right(fd, root->right);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &g_lbv.exit_status, 0);
	waitpid(-1, &g_lbv.exit_status, 0);
}

void	execution(t_parser_node *root)
{
	if (root == NULL)
		return ;
	if (root->type == PIPE)
		pipe_fork(root);
	else if (root->type == CMD)
	{
		if (root->rdrlst)
			redirection(root);
		else
			execution_cmd(root);
	}
}
