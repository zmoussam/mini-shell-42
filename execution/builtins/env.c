/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:16:21 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 00:44:57 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check__()
{
	t_env_node *head;
	
	head = g_lbv.list;
	while (head)
	{
		if (ft_strcmp(head->name, "_") == 0)
			return ;
		head = head->next;
	}
	printf("_=/Users/zmoussam/Desktop/minishell/./minishell\n");
}

void	env_cmd(t_parser_node *root)
{
	if (root->ac != 1)
	{
		if (root->av[1][0] == '-')
		{
			printf("env: illegall option %s\n", root->av[1]);
			printf("usage: env whit no option or argument\n");
			g_lbv.exit_status = 256;
			return ;
		}
		else
			printf("env: %s: No such file or directory\n", root->av[1]);
		g_lbv.exit_status = 127 * 256;
	}
	else
	{
		print_list();
		check__();
		g_lbv.exit_status = 0;
	}
}
