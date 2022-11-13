/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 01:34:14 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	remove_old_variable(t_env_node *new_node, int *i)
{
	if (!ft_strcmp(new_node->name, "PATH") && new_node->content[0] == '\0')
	{
		*i += 1;
		delone_env(new_node);
		return (1);
	}
	else
		ft_list_remove_if(&g_lbv.list, new_node->name);
	return (0);
}

void	add_export_variable(char **argv)
{
	t_env_node	*new;
	int			i;
	int			_check_parse;
	int			check_exit_status;

	i = 1;
	check_exit_status = 0;
	while (argv[i])
	{
		if (argv[i][0] == ';' || argv[i][0] == '#')
			break ;
		new = get_new_node(argv[i]);
		if (!new)
			return ;
		_check_parse = parss_export_variable(new, i, &check_exit_status);
		if (_check_parse)
		{
			if (_check_parse == -1 && i == 1)
			{
				check_exit_status = 512;
				delone_env(new);
				break ;
			}
			i++;
			delone_env(new);
			continue ;
		}
		if (env_find(g_lbv.list, new->name, ft_strlen(new->name)))
			if (remove_old_variable(new, &i))
				continue ;
		add_back(&g_lbv.list, new);
		i++;
	}
	g_lbv.exit_status = check_exit_status;
}

void	export(t_parser_node *root)
{
	if (root->ac == 1 || (root->ac == 2 \
		&& (root->av[1][0] == '#' || root->av[1][0] == ';')))
	{
		print_sort_list();
		g_lbv.exit_status = 0;
	}
	else
		add_export_variable(root->av);
}
