/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:42 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 00:09:07 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../execution/execution.h"
#include <fcntl.h>

void    *redirect_input(t_parser_node *node, t_rdr_node *rdrlst, int v, int *input_file)
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
            redirect_output(node, head, 0, &out_put_file);
        head = head->next;
    }
    *input_file = fd;
    printf("head->inputfile %d\n", *input_file);
    if (v == 1)
    {
        pid = fork();
        if (pid == -1)
            printf("minishell: %s\n", strerror(errno));
        else if (pid == 0)
        {
            dup2(fd, STDIN_FILENO);
            dup2(out_put_file, STDOUT_FILENO);
            close(fd);
            execution_cmd(node);      
            exit(0);
        }
        waitpid(pid, NULL, 0);
    }
    return (0);  
}

void    *redirect_output(t_parser_node *node, t_rdr_node *rdrlst, int v, int *out_put_file)
{
    t_rdr_node  *head;
    int         input_file;
    int fd = 0;
    int pid;
    
    head = rdrlst;
    input_file = 0;
    printf("kharya\n");
    while (head)
    {
        if (head->type == RD_OUT)
            fd = open(head->file, O_CREAT | O_RDWR | O_TRUNC, 0777);
        else if (head->type ==  RD_APP)
            fd = open(head->file, O_CREAT | O_RDWR | O_APPEND, 0777);
        else
            redirect_input(node, head, 0, &input_file);
        head = head->next;
    }
    if (fd == -1)
    {
        if (node->rdrlst->file[0] == '\0')
            printf("minishell: !! ambiguous redirect\n");
        else
            printf("minishell: %s\n", strerror(errno)); 
    }
    else 
    {
        *out_put_file = fd;
        if (v == 1)
        {
            pid = fork();
            if (pid == -1)
                printf("minishell: %s\n", strerror(errno));
            else if (pid == 0)
            {
                dup2(fd, STDOUT_FILENO);
                dup2(input_file, STDIN_FILENO);
                close(fd);
                execution_cmd(node);  
                exit(0);
            }
            waitpid(pid, NULL, 0);
        }
    }
    return (NULL);
}

void *herdoc_(t_parser_node *node, t_rdr_node *rdrlst)
{
    t_rdr_node *head;
    t_rdr_node *tmp;
    int         herdoc_file = 0;
    int         pid;
    int         v = 1;
    int input_file = 0;
    int output_file = 1;
    
    tmp = rdrlst;
    head = rdrlst;
    while(tmp->next && tmp->next->type == HERDOC)
        tmp = tmp->next;
    while (head)
    {
        if (head->type == RD_OUT || head->type == RD_APP)
        {
            redirect_output(node, head, 0, &output_file);
        }
        if (head->type == RD_IN)
        {     
            v = 0;
            redirect_input(node, head, 0, &input_file);
        }
        head = head->next;
    }
    pid = fork();
    if (pid == -1)
        printf("minishell: %s\n", strerror(errno)); 
    else if (pid == 0)
    {
        if (v == 1)
            herdoc_file = open(tmp->file, O_RDWR, 0777);
        else 
            herdoc_file = input_file;
        if (herdoc_file == -1)
            printf("minishell1: %s\n", strerror(errno));
        else 
        {
            dup2(herdoc_file, STDIN_FILENO);
            dup2(output_file, STDOUT_FILENO);
            close(herdoc_file);
            execution_cmd(node);  
            exit(0);
        }
    }
    waitpid(pid, NULL, 0);
    return (NULL);
}
void    redirection(t_parser_node *node)
{
    int output_file;
    int input_file;
    
    output_file = 1;
    input_file = 0;
    if (node->rdrlst->type == HERDOC)
        herdoc_(node, node->rdrlst);
    else if (node->rdrlst->type == RD_OUT || node->rdrlst->type == RD_APP)
         redirect_output(node, node->rdrlst, 1, &output_file);
    else if (node->rdrlst->type == RD_IN)
         redirect_input(node, node->rdrlst, 1, &input_file);
}