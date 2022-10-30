/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/30 21:02:58 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <unistd.h>

void	cd(t_node *root)
{
	static char	*oldpwd;
	char		*tmp_cwd;
	char		*tmp_content;

	tmp_cwd = NULL;
	if (oldpwd != NULL)
		tmp_cwd = ft_strdup(oldpwd);
	if (root->argc == 1)
	{
		if (env_find(env_list, "HOME", -1))
		{
			tmp_content = env_find(env_list, "HOME", -1)->content;
			oldpwd = getcwd(NULL, 0);
			ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
			add_back(&env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			if (chdir(tmp_content) == -1)
			{
				printf("minishell: cd: %s:No such file or directory\n", \
					tmp_content);
				oldpwd = tmp_cwd;
				ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
				add_back(&env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
				return ;
			}
		}
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if (root->argc > 1)
	{
		if (ft_strcmp(root->argv[1], "-") == 0)
		{
			if (oldpwd != NULL)
			{
				ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
				oldpwd = getcwd(NULL, 0);
				add_back(&env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			}
			if (env_find(env_list, "OLDPWD", -1) == NULL \
				|| chdir(tmp_cwd) == -1)
				printf("minishe v0.1: cd: OLDPWD not set\n");
			else
				printf("%s\n", oldpwd);
			return ;
		}
		else
		{
			ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
			oldpwd = getcwd(NULL, 0);
			add_back(&env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			if (chdir(root->argv[1]) == -1)
			{
				printf("minishell: cd: %s:no such file or directory\n", \
					root->argv[1]);
				oldpwd = tmp_cwd;
				ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
				if (oldpwd != NULL)
					add_back(&env_list, new_node(oldpwd, \
						ft_strdup("OLDPWD"), 6));
			}
		}
	}
}
