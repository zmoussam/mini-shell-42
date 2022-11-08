/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:42 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/08 20:50:57 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../execution/execution.h"
#include <fcntl.h>

t_rdr_node    *redirect_input(t_parser_node *node, t_rdr_node *rdrlst, int v, int *input_file)
{
    t_rdr_node  *head;
    int pid;
    int fd;
    int out_put_file;
    
    head = rdrlst;
    out_put_file = 1;
    while (head)
    {
        if (head->type == RD_IN)
        {
            fd = open(head->file, O_RDWR, 0777);
            if (fd == -1)
                return (printf("minishell: %s: %s\n", head->file, strerror(errno)), NULL);  
        }
        else if (head->type == RD_OUT || head->type == RD_APP)
        { 
            redirect_output(node, head, 0, &out_put_file);
            // break;
        }
        head = head->next;
    }
    *input_file = fd;
    pid = fork();
    if (pid == -1)
        printf("minishell: %s\n", strerror(errno));
    else if (pid == 0)
    {
        if (v == 1)
        {
            dup2(fd, STDIN_FILENO);
            dup2(out_put_file, STDOUT_FILENO);
            close(fd);
            execution_cmd(node);      
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return (0);  
}

t_rdr_node    *redirect_output(t_parser_node *node, t_rdr_node *rdrlst, int v, int *out_put_file)
{
    t_rdr_node  *head;
    int         input_file;
    int fd = 0;
    int pid;
    
    head = rdrlst;
    input_file = 0;
    while (head)
    {
        if (head->type == RD_OUT)
            fd = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
        else if (head->type ==  RD_APP)
            fd = open(head->file, O_CREAT | O_RDWR | O_APPEND, 0777);
        else
        {
            redirect_input(node, head, 0, &input_file);
            // break;
        }
        head = head->next;
    }
    if (fd == -1)
        printf("%s\n", strerror(errno));
    else 
    {
        *out_put_file = fd;
        pid = fork();
        if (pid == -1)
            printf("%s\n", strerror(errno));
        else if (pid == 0)
        {
            //close(STDOUT_FILENO);
            if (v == 1)
            {
                dup2(fd, STDOUT_FILENO);
                dup2(input_file, STDIN_FILENO);
                close(fd);
                execution_cmd(node);  
            }
            exit(0);
        }
        waitpid(pid, NULL, 0);
    }
    return (NULL);
}
void    redirection(t_parser_node *node)
{
    int out_put_file;
    int input_file;
    
    out_put_file = 1;
    input_file = 0;
    
        if (node->rdrlst->type == RD_OUT || node->rdrlst->type == RD_APP)
           node->rdrlst = redirect_output(node, node->rdrlst, 1, &out_put_file);
        else if (node->rdrlst->type == RD_IN)
            node->rdrlst = redirect_input(node, node->rdrlst, 1, &input_file);
}