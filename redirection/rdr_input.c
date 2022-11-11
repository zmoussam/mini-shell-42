/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:38:06 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 23:17:28 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	execute_rdr_input_cmd(t_parser_node *node, t_out_in_file *file)
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

int	get_input_file(t_parser_node *node, t_rdr_node *head, t_out_in_file *file)
{
	if (head->type == RD_IN && file->input_file != -1 \
		&& file->output_file != -1)
	{
		if (file->input_file != 0)
			close(file->input_file);
		file->input_file = open(head->file, O_RDWR, 0777);
	}
	else if ((head->type == RD_OUT || head->type == RD_APP) \
		&& (file->input_file != -1 && file->output_file != -1))
		rdr_output(node, head, file, 0);
	if (file->input_file == -1 || file->output_file == -1)
	{
		if (head->file[0] == '\0')
			return (printf("minishell: !! ambiguous redirect\n"));
		return (printf("minishell: %s: %s\n", head->file, strerror(errno)));
	}
	return (0);
}

void	*rdr_input(t_parser_node *n, t_rdr_node *l, t_out_in_file *file, int v)
{
	t_rdr_node	*head;

	head = l;
	while (head)
	{
		get_input_file(n, head, file);
		if (file->output_file == -1 || file->input_file == -1)
			return (NULL);
		head = head->next;
	}
	if (v == 1 && file->input_file != -1 && file->output_file != -1)
		execute_rdr_input_cmd(n, file);
	return (NULL);
}
