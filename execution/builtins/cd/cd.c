/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 23:27:57 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <unistd.h>

void	go_to_newpath(char **oldpwd, char *path, char **pwd)
{
	char	*tmp_cwd;

	tmp_cwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		g_lbv.exit_status = 256;
		return (printf("minishell: cd: %s:%s\n", path, \
			strerror(errno)), free(tmp_cwd));
	}
	else
	{
		if (oldpwd == NULL)
			add_back(&g_lbv.list, new_node(tmp_cwd, ft_strdup("OLDPWD"), 6));
		else
			set_oldpwd(oldpwd, tmp_cwd, 0);
		set_pwd(pwd);
		g_lbv.exit_status = 0;
	}
}

void	cd(t_parser_node *root)
{
	char		**oldpwd;
	t_env_node	*tmp_env_oldpwd;
	t_env_node	*tmp_env_pwd;
	char		**pwd;

	oldpwd = NULL;
	pwd = NULL;
	tmp_env_oldpwd = env_find(g_lbv.list, "OLDPWD", 6);
	if (tmp_env_oldpwd)
		oldpwd = &(tmp_env_oldpwd->content);
	tmp_env_pwd = env_find(g_lbv.list, "PWD", 3);
	if (tmp_env_pwd)
		pwd = &(tmp_env_pwd->content);
	if (root->ac == 1 || ft_strcmp(root->av[1], "~" ) == 0 \
	|| ft_strcmp(root->av[1], "--" ) == 0)
		go_to_home(oldpwd, pwd, env_find(g_lbv.list, "HOME", 4), \
		getcwd(NULL, 0));
	else if (root->ac > 1)
	{
		if (ft_strcmp(root->av[1], "-") == 0)
			go_to_oldpath(oldpwd, pwd);
		else
			go_to_newpath(oldpwd, root->av[1], pwd);
	}
}
