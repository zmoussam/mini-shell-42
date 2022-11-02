/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/01 08:52:03 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <unistd.h>

int	go_to_oldpath(char **oldpwd, char *tmp_cwd)
{
	if (env_find(g_env_list, "OLDPWD", -1) == NULL)
		{
			printf("minishell: cd: OLDPWD not set\n");
			free(tmp_cwd);
			return (1);
		}
		else if (*oldpwd != NULL)
		{
			ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
			*oldpwd = getcwd(NULL, 0);
			add_back(&g_env_list, new_node(*oldpwd, ft_strdup("OLDPWD"), 6));
		}
		if (chdir(tmp_cwd) == -1) // check !! if we set HOME manuel
			printf("minishell: cd: %s:%s\n", tmp_cwd, strerror(errno));
		else
			printf("%s\n", *oldpwd);
		free(tmp_cwd);
	return (0);
} 
void	go_to_home(char **oldpwd, char *tmp_cwd)
{
	char	*tmp_content;

	tmp_content = NULL;
	if (env_find(g_env_list, "HOME", -1))
		{
			tmp_content = env_find(g_env_list, "HOME", -1)->content;
			ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
			*oldpwd = getcwd(NULL, 0);
			add_back(&g_env_list, new_node(*oldpwd, ft_strdup("OLDPWD"), 6));
			if (chdir(tmp_content) == -1)
			{
				printf("minishell: cd: %s:%s\n", \
					tmp_content, strerror(errno));
				*oldpwd = tmp_cwd;
				ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
				if (*oldpwd != NULL)
					add_back(&g_env_list, new_node(*oldpwd, ft_strdup("OLDPWD"), 6));
				return ;
			}
		}
		else
			printf("minishell: cd: HOME not set\n");
		free(tmp_cwd);
}
void	cd(t_node *root)
{
	static char	*oldpwd;
	char		*tmp_cwd;

	tmp_cwd = NULL;
	if (oldpwd != NULL)
		tmp_cwd = ft_strdup(oldpwd);
	if (root->argc == 1 || ft_strcmp(root->argv[1], "~" ) == 0 \
	|| ft_strcmp(root->argv[1], "--" ) == 0)
	{
		go_to_home(&oldpwd, tmp_cwd);
	}
	else if (root->argc > 1)
	{
		if (ft_strcmp(root->argv[1], "-") == 0)
		{
			// if (go_to_oldpath(&oldpwd, tmp_cwd))
			// 	return ;
			if (env_find(g_env_list, "OLDPWD", -1) == NULL)
			{
				printf("minishell: cd: OLDPWD not set\n");
				free(tmp_cwd);
				return ;
			}
			else if (oldpwd != NULL)
			{
				ft_list_remove_if(&g_env_list, "OLDPWD", &ft_strcmp);
				oldpwd = getcwd(NULL, 0);
				add_back(&g_env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
			}
			if (chdir(tmp_cwd) == -1) // check !! if we set HOME manuel
				printf("minishell: cd: %s:%s\n", \
					tmp_cwd, strerror(errno));
			else
				printf("%s\n", oldpwd);
			free(tmp_cwd);
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
			else
				free(tmp_cwd);
		}
	}
}