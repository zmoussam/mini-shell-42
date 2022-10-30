/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:55 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/30 18:15:44 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	unset(t_node *root)
{
    int i;
    int j;
	
	i = 1;
	j = 0;
	if (root->argc > 1)
	{
		if (root->argv[1][0] == '-')
		{
			printf("minishell v0.1: unset: %s: invalid option\n", root->argv[1]);
			printf("unset: usage: unset [-f] [name ...]\n");
		}
		else if (root->argc >= 2)
		{
			while (root->argv[i])
			{
				j = 0;
				while (root->argv[i][j])
				{
					if (j == 0 && ft_isdigit(root->argv[i][j]))
					{
						printf("minishell: unset: %s: not a valid identifier\n", root->argv[i]);
						break;
					}
					if ((root->argv[i][j] <= 64 && !ft_isdigit(root->argv[i][j])) \
					|| (root->argv[i][j] >= 91 && root->argv[i][j] <= 96) \
					|| root->argv[i][j] >= 123)
					{
						printf("minishell: unset: %s: not a valid identifier\n", root->argv[i]);
						break;
					}
					j++;
				}
				if (env_find(env_list, root->argv[i], -1))
					ft_list_remove_if(&env_list, root->argv[i], &ft_strcmp);
				i++;	
			}
		}
	}
}