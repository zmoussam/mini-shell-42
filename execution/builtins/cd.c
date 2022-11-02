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

void	go_to_newpath(char **oldpwd, char *path)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return(printf("minishell: cd: %s:%s\n", path, strerror(errno)), free(tmp_cwd));
	else
	{
		if (oldpwd == NULL)
			add_back(&g_env_list, new_node(tmp_cwd, ft_strdup("OLDPWD"), 6));
		else
		{
			free(*oldpwd);
			*oldpwd = tmp_cwd;
		}
	}

}
void	go_to_oldpath(char **oldpwd)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (printf("minishell: cd: OLDPWD not set\n"), free(tmp_cwd));
	else
	{
		if (chdir(*oldpwd) == -1)
			return (printf("minishell: cd: %s:%s\n", tmp_cwd, strerror(errno)), free(tmp_cwd));
		else
		{
			printf("%s\n", tmp_cwd);
			free(*oldpwd);
			*oldpwd = tmp_cwd;
		}
	}
} 
void	go_to_home(char **oldpwd)
{
	char		*tmp_old;
	char		*home;
	t_env_list	*tmp_env_home;

	home = NULL;
	tmp_env_home = env_find(g_env_list, "HOME", 4);
	if (tmp_env_home)
		home = tmp_env_home->content;
	tmp_old = getcwd(NULL, 0);
	if (home)
	{
		if (chdir(home) == -1)
			return(printf("minishell: cd: %s:%s\n", home, strerror(errno)), free(tmp_old));
		else if (oldpwd == NULL)
			add_back(&g_env_list, new_node(tmp_old, ft_strdup("OLDPWD"), 6));
		else
		{
			free(*oldpwd);
			*oldpwd = tmp_old;
		}
	}
	else
		printf("minishell: cd: HOME not set\n");
}
void	cd(t_node *root)
{
	char		**oldpwd;
	t_env_list *tmp_env_oldpwd;

	oldpwd = NULL;
	tmp_env_oldpwd = env_find(g_env_list, "OLDPWD", 6);
	if (tmp_env_oldpwd)
		oldpwd = &(tmp_env_oldpwd->content);
	if (root->argc == 1 || ft_strcmp(root->argv[1], "~" ) == 0 \
	|| ft_strcmp(root->argv[1], "--" ) == 0)
		go_to_home(oldpwd);
	else if (root->argc > 1)
	{
		if (ft_strcmp(root->argv[1], "-") == 0)
			go_to_oldpath(oldpwd);
		else
			go_to_newpath(oldpwd, root->argv[1]);
	}
}