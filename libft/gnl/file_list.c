/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:06:17 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "file.h"
#include <stdlib.h>

t_list	*ft_file_find(t_list *lst, int fd)
{
	while (lst)
	{
		if (((t_file *)lst->content)->fd == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_file	*ft_file_get(t_list *lst, int fd)
{
	t_list	*node;

	node = ft_file_find(lst, fd);
	if (node)
		return (node->content);
	return (NULL);
}

t_file	*ft_file_get_or_create(t_list **lst, int fd)
{
	t_file	*f;
	t_list	*node;

	f = ft_file_get(*lst, fd);
	if (f)
		return (f);
	f = ft_file_new(fd);
	if (!f)
		return (NULL);
	node = ft_lstnew(f);
	if (!node)
	{
		free(f);
		return (NULL);
	}
	ft_lstadd_front(lst, node);
	return (f);
}

void	ft_file_delete(t_list **lst, int fd)
{
	t_list	*node;

	node = ft_file_find(*lst, fd);
	if (node)
	{
		ft_lstremove(lst, node);
		ft_lstdelone(node, free);
	}
}
