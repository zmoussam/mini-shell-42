/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:35:06 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 01:31:24 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../parsing/parser.h"
#include "../execution/execution.h"

void	_shell_level(void)
{
	t_env_node	*head;
	char		*shlvl;

	head = g_lbv.list; 
	while (head)
	{
		if (ft_strcmp(head->name, "SHLVL") == 0)
		{
			shlvl = ft_itoa((ft_atoi(head->content) + 1));
			if (!shlvl)
				return (printf("minishell: memory was not allocated!\n"), \
				(void)0);
			free(head->content);
				head->content = shlvl;
			return ;
		}
		head = head->next;
	}
	add_back(&g_lbv.list, new_node(ft_strdup("1"), ft_strdup("SHLVL"), 5));
}

void _set_pwd(void)
{
	t_env_node *head;
	
	head = g_lbv.list;
	while (head)
	{
		if (ft_strcmp(head->name, "PWD") == 0)
			return ;
		head = head->next;
	}
	add_back(&g_lbv.list, new_node(getcwd(NULL, 0), ft_strdup("PWD"), 3));
		
}