/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_sorted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:08:48 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 01:50:48 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinsert_sorted(t_list **lst, t_list *new, t_lft_cmpfn cmp)
{
	t_list	*curr;
	t_list	*prev;

	curr = *lst;
	if (!curr || cmp(curr->content, new->content) > 0)
		ft_lstadd_front(lst, new);
	else
	{
		prev = curr;
		curr = curr->next;
		while (curr && cmp(curr->content, new->content) <= 0)
		{
			prev = curr;
			curr = curr->next;
		}
		new->next = curr;
		prev->next = new;
	}
}
