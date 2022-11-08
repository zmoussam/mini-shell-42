/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:42 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/08 18:15:28 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../execution/execution.h"
#include <fcntl.h>

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
    t_rdr_node  *head;
    int fd = 0;
    int pid;
    
    head = node->rdrlst;
    while (head)
    {
        if (head->type == RD_OUT)
            fd = open(head->file, O_CREAT | O_RDWR | O_TRUNC);
        else if (head->type ==  RD_APP)
            fd = open(head->file, O_CREAT | O_RDWR | O_APPEND);
        head = head->next; 
    }
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
    
    if (node->rdrlst->type == RD_OUT || node->rdrlst->type == RD_APP)
    {
         redirect_output(node);
    }
   	else if (node->rdrlst->type == RD_IN)
		redirect_input(node);
}