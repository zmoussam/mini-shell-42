/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 21:23:32 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "execution.h"
#include<string.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "../redirection/redirection.h"

void	execute_left(int *fd, t_parser_node *left)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execution(left);
	exit(127);
}

void	execute_right(int *fd, t_parser_node *right)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
