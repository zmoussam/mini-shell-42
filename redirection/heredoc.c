/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:40:52 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 23:03:09 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

char	*get_herdoc_file(t_rdr_node *rdrlst)
{
	t_rdr_node	*head;
	t_rdr_node	*herdoc_file;

	head = rdrlst;
	herdoc_file = NULL;
	while (head)
	{
		if (head->type == HERDOC)
			herdoc_file = head;
		head = head->next;
	}
	return (herdoc_file->file);
}

void	execute_heredoc_cmd(t_parser_node *node, t_out_in_file *file)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		printf("minishell: %s\n", strerror(errno));
	else if (pid == 0)
	{
		dup2(file->input_file, STDIN_FILENO);
		dup2(file->output_file, STDOUT_FILENO);
		execution_cmd(node);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	*herdoc_(t_parser_node *n, t_rdr_node *lst, t_out_in_file *file, int v)
{
	t_rdr_node	*head;
	char		*tmp;

	tmp = get_herdoc_file(lst);
	file->input_file = open(tmp, O_RDWR, 0777);
	if (file->input_file == -1 || file->output_file == -1)
		return (printf("minishell: %s\n", strerror(errno)), NULL);
	head = lst;
	while (head)
	{
		if ((head->type == RD_OUT || head->type == RD_APP) \
			&& (file->input_file != -1 && file->output_file != -1))
			rdr_output(n, head, file, 0);
		if (head->type == RD_IN && file->input_file != -1 \
			&& file->output_file != -1)
			rdr_input(n, head, file, 0);
		head = head->next;
	}
	if (v == 1 && file->input_file != -1 && file->output_file != -1)
		execute_heredoc_cmd(n, file);
	return (NULL);
}
