/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:55 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/04 01:10:31 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	print_unset_error(char *argv, int *check)
{
	*check = 1;
	printf("minishell: unset: %s: not a valid identifier\n", argv);
}

void	parse_unset_variable(char *argv, int *check)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[0]))
	{
		print_unset_error(argv, check);
		return ;
	}
	while (argv[i] && *check == 0)
	{
		if ((argv[i] <= 64 \
		&& !ft_isdigit(argv[i])) \
		|| (argv[i] >= 91 && argv[i] <= 96 \
		&& argv[i] != '_') || argv[i] >= 123)
			print_unset_error(argv, check);
		i++;
	}
}

void	unset(t_node *root)
{
	int	i;
	int	k;

	i = 1;
	if (root->argc > 1)
	{
		if (root->argv[1][0] == '-')
		{
			printf("minishell: unset: %s: invalid option\n", root->argv[1]);
			printf("unset: usage: unset [-f] [name ...]\n");
		}
		else if (root->argc >= 2)
		{
			while (root->argv[i])
			{
				k = 0;
				parse_unset_variable(root->argv[i], &k);
				if (k == 0 && env_find(g_env_list, root->argv[i], -1))
					ft_list_remove_if(&g_env_list, root->argv[i]);
				i++;
			}
		}
	}
}
