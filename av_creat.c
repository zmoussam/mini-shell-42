/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_creat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:58:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 13:25:57 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**av_creat(t_cmd **lst)
{
	char		**av;
	int			i;
	int			size;
	t_cmd		*cmd;
	t_wc_node	*tmp;

	i = 0;
	cmd = NULL;
	size = cmd_size(*lst);
	av = malloc(sizeof(char *) * (size + 1));
	if (!av)
		return (NULL);
	while (*lst)
	{
		if ((*lst)->wc)
		{
			while ((*lst)->wc)
			{
				av[i++] = (*lst)->wc->d_name;
				tmp = (*lst)->wc;
				(*lst)->wc = (*lst)->wc->next;
				free(tmp);
			}
		}
		else
			av[i++] = remove_q((*lst)->word);
		cmd = *lst;
		*lst = (*lst)->next;
		free(cmd);
	}
	av[i] = 0;
	return (av);
}
