/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:11:40 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/08 16:34:37 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "execution.h"
#include<string.h>
#include <fcntl.h>
#include <sys/errno.h>

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

void    redirect_input(t_parser_node *node)
{
    int pid;
    int fd;
    
    fd = open(node->rdrlst->file, O_RDWR, 0777);
    if (fd == -1)
        printf("%s\n", strerror(errno));
    pid = fork();
    if (pid == -1)
        printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
        execution_cmd(node);
        exit(0);
    }
	waitpid(pid, NULL, 0);
}

void    redirect_output(t_parser_node *node)
{
    int fd = 0;
    int pid;
    
    if (node->rdrlst->type == RD_OUT)
        fd = open(node->rdrlst->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
    else if (node->rdrlst->type ==  RD_APP)
        fd = open(node->rdrlst->file, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd == -1)
        printf("%s\n", strerror(errno));
    pid = fork();
    if (pid == -1)
        printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
         //close(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execution_cmd(node);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
void    redirection(t_parser_node *node)
{   
    if (node->rdrlst->type == RD_OUT|| node->rdrlst->type == RD_APP)
         redirect_output(node);
   	else if (node->rdrlst->type == RD_IN)
		redirect_input(node);
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