/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:47:27 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/14 00:17:35 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_node	*lstlast(t_env_node *lst)
{
	if (!lst)
		return (0);
	while (!(lst->next == NULL))
		lst = lst->next;
	return (lst);
}

void	add_back(t_env_node **lst, t_env_node *new)
{
	t_env_node	*p;

	if (!new)
		return (printf("minishell:memory was not allocated!\n"), (void)0);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = lstlast(*lst);
	p->next = new;
}

t_env_node	*new_node(char *content, char *name, int len)
{
	t_env_node	*s;

	s = (t_env_node *)malloc(sizeof(t_env_node));
	if (s == NULL)
		return (printf("minishell:memory was not allocated!\n"), NULL);
	if (!name)
		return (printf("minishell:memory was not allocated!\n"), free(s), NULL);
	if (!content)
		return (printf("minishell:memory was not allocated!\n"), \
		free(s), free(name), NULL);
	s->content = content;
	s->name = name;
	s->len = len;
	s->next = NULL;
	return (s);
}

void	delone_env(t_env_node *node)
{
	free(node->name);
	free(node->content);
	free(node);
}
