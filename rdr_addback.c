/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:21:23 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 15:06:57 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	rdr_clear(t_rdr_node **lst)
{
	t_rdr_node	*tmp;

	tmp = NULL;
	if (!lst)
		return ;
	while (*lst && *lst != MISSMATCH)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free((tmp->file));
		free(tmp);
	}
}

void	rdr_addback(t_rdr_node **lst, t_rdr_node *new)
{
	t_rdr_node	*p;

	p = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (p != MISSMATCH && p->next)
		p = p->next;
	if (p != MISSMATCH)
	{
		p->next = new;
		new->next = NULL;
	}
}