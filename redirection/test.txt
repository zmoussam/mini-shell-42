/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:18:15 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/27 22:53:16 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "redirection.h"
#include<errno.h>

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		size;
	int		j;

	size = 0;
	while (s1[size])
		size++;
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (copy == NULL)
		return (copy);
	j = 0;
	while (s1[j])
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

typedef struct t_temp{
    char    **argv;
    int     argc;
}t_temp;
void    execution_cmd2(t_temp *cmd)
{
    if (execve("/bin/ls",cmd->argv ,NULL) == -1)
		printf("%s\n", strerror(errno));
}
void    redirect_output(char *file_name, t_temp *cmd, int type)
{
    int fd;
    int pid;
    
    if (type == RDC_OUT)
        fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
    else if (type ==  DBL_RDC_OUT)
        fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd == -1)
        printf("%s\n", strerror(errno));
    pid = fork();
    if (pid == -1)
        printf("%s", strerror(errno));
    else if (pid == 0)
    {
         //close(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execution_cmd2(cmd);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
void    redirect_input(char *file_name, t_temp *cmd)
{
    int pid;
    int fd;

    fd = open(file_name, O_RDWR, 0777);
    if (fd == -1)
        printf("%s\n", strerror(errno));
    pid = fork();
    if (pid == -1)
        printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
        dup2(fd, STDIN_FILENO);
        close(fd);
        execution_cmd2(cmd);
        exit(0);
    }
    
}
int main(int argc, char **argv)
{
    t_redc *node;
    t_temp *cmd;
    int i = 1;
    int j = 0;
    cmd = (t_temp *)malloc(sizeof(t_temp));
    cmd->argv = (char **)malloc(sizeof(char *) * argc + 1);
    node = (t_redc *)malloc(sizeof(t_redc));
    node->type = RDC_OUT;
    node->file_name = "test.txt";
    node->next = NULL;
    cmd->argc = argc;
    
    while (i < argc)
    {
        cmd->argv[j] = ft_strdup(argv[i]);
        i++;
        j++;
    }
    cmd->argv[j] = NULL;
    
    // printf("node->type = %d\n node->file_name = %s\n", node->type, node->file_name);
   //printf("cmd->argc = %d \ncmd = %s\ncmd->arg = %s\n", cmd->argc, cmd->argv[0], cmd->argv[1]);
    // redirect_output(node->file_name, cmd, node->type);
    redirect_input(node->file_name, cmd);
}

//gedit
// /bin/sysinfo
