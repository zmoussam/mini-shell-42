/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:32:37 by syakoubi          #+#    #+#             */
/*   Updated: 2022/01/04 20:12:23 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_lstremove(t_list **lst, t_list *to_remove)
{
	t_list	*current;
	t_list	*previous;

	current = *lst;
	previous = NULL;
	while (current)
	{
		if (current == to_remove)
		{
			if (previous)
				previous->next = current->next;
			else
				*lst = current->next;
			return ;
		}
		previous = current;
		current = current->next;
	}
}
