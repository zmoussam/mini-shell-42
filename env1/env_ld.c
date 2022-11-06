/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:47:27 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/06 19:48:18 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	*lstlast(t_env_list *lst)
{
	if (!lst)
		return (0);
	while (!(lst->next == NULL))
		lst = lst->next;
	return (lst);
}


void	add_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*p;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = lstlast(*lst);
	p->next = new;
}

t_env_list	*new_node(char *content, char *name, int len)
{
	t_env_list	*s;

	s = (t_env_list *)malloc(sizeof(t_env_list));
	if (s == NULL)
		return (NULL);
	s->content = content;
    s->name = name;
    s->len = len;
	s->next = NULL;
	return (s);
}

void	delone_env(t_env_list *node)
{
	free(node->name);
	free(node->content);
	free(node);
}