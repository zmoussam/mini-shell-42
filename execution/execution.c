/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/08 21:18:07 by zmoussam         ###   ########.fr       */
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
		env_cmd(root->ac);
	else if (ft_strcmp(root->av[0], "cd") == 0)
		cd(root);
	else if (ft_strcmp(copy, "pwd") == 0)
		pwd(root);
	else if (ft_strcmp(root->av[0], "unset") == 0)
		unset(root);
	else if (ft_strcmp(root->av[0], "exit") == 0)
		exit_cmd(root);
	else if (ft_strcmp(root->av[0], "export") == 0)
		export(root);
	else
		launch_executabl(root);
	free(copy);
}

void	execute_left(int *fd, t_parser_node *left)
{
	close(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execution(left);
	exit(0);
}

void	execute_right(int *fd, t_parser_node *right)
{
	close(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	execution(right);
	exit(0);
}

void	execution(t_parser_node *root)
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
		pid = fork();
		if (pid == 0)
			execute_right(fd, root->right);
		close(fd[0]);
		close(fd[1]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
	else if (root->type == CMD)
	{
		if (root->rdrlst)
			redirection(root);
		else
			execution_cmd(root);
	}
}