/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:43:44 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/12 11:46:09 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_cmd	*ft_new_cmd(char *content, t_wc_node **list)
{
	t_cmd	*s;

	s = (t_cmd *)malloc(sizeof(t_cmd));
	if (!s)
		return (NULL);
	s->word = content;
	s->wc = NULL;
	s->next = NULL;
	if (list)
		s->wc = *list;
	return (s);
}

void	cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = cmd_lstlast(*lst);
	p->next = new;
}

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (!(lst->next == NULL))
		lst = lst->next;
	return (lst);
}

int	cmd_size(t_cmd *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->wc)
		{
			i += wc_size(lst->wc);
			lst = lst->next;
		}
		else
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

void	cmd_clear(t_cmd **lst)
{
	t_cmd	*tmp;

	tmp = 0;
	if (!lst)
		return ;
	while (*lst)
	{
		if ((*lst)->wc)
		{
			wc_clear(&(*lst)->wc);
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp);
		}
		else
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp->word);
			free(tmp);
		}
	}
}
