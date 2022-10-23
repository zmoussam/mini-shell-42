/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:55 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/23 16:10:48 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	unset(t_node *root)
{
    int i;
	
	i = 1;
	if (root->argc == 1)
		printf("Usage: unset [-nfv] name...\n");
	else if(root->argv[1][0] == '-')
		printf("/minishell v0.1: unset: %s: unknown option\n", root->argv[1]);
	else if (root->argc >= 2)
	{
		while (root->argv[i])
		{
			if (root->argv[i][0] == 32)
				printf("unset:%s: invalid parameter name\n", root->argv[i]);
			if (env_find(env_list, root->argv[i], -1))
				ft_list_remove_if(&env_list, root->argv[i], &ft_strcmp);
			i++;	
		}
	}
}