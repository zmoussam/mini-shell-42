/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 22:24:09 by zmoussam         ###   ########.fr       */
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
		tmp_cwd = oldpwd;
	if (root->argc == 1)
	{
		if (env_find(g_env_list, "HOME", -1))
		{
			tmp_content = env_find(g_env_list, "HOME", -1)->content;
			oldpwd = getcwd(NULL, 0);
			ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
			add_back(&g_env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			if (chdir(tmp_content) == -1)
			{
				printf("minishell: cd: %s:%s\n", \
					tmp_content, strerror(errno));
				oldpwd = tmp_cwd;
				ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
				add_back(&g_env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
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
				ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
				oldpwd = getcwd(NULL, 0);
				add_back(&g_env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			}
			if (env_find(g_env_list, "OLDPWD", -1) == NULL)
				printf("minishell: cd: OLDPWD not set\n");
			else if(chdir(tmp_cwd) == -1)
				printf("minishell: cd: %s:%s\n", \
					tmp_cwd, strerror(errno));
			else
				printf("%s\n", oldpwd);
			return ;
		}
		else
		{
			ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
			oldpwd = getcwd(NULL, 0);
			add_back(&g_env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			if (chdir(root->argv[1]) == -1)
			{
				printf("minishell: cd: %s:%s\n", \
					root->argv[1], strerror(errno));
				ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
				oldpwd = tmp_cwd;	
				if (oldpwd != NULL)
				{
					add_back(&g_env_list, new_node(oldpwd, \
						ft_strdup("OLDPWD"), 6));	
				}
			}
		}
	}
}
