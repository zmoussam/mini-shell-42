/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:26:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/23 16:10:53 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include <unistd.h>

void    cd(t_node *root)
{  
    char *oldpwd;
    char *first_cwd;
    
    oldpwd = NULL;
    first_cwd = getcwd(NULL, 0);
    if (env_find(env_list, "OLDPWD", -1) != NULL)
    {
        oldpwd = (env_find(env_list, "OLDPWD", 6)->content);
        ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
        add_back(&env_list, new_node(getcwd(NULL, 0), ft_strdup("OLDPWD"), 6));
    }
    if (root->argc == 1 || (root->argc == 2 && (ft_strcmp(root->argv[1], "~") == 0 || ft_strcmp(root->argv[1], "--") == 0)))
    {
        if (env_find(env_list, "HOME", -1))
            if (chdir(env_find(env_list, "HOME", -1)->content) == -1)
            {
                printf("error in changin directory\n");
                return ;
            }
    }
    else if (root->argc == 2)
    {
        if (ft_strcmp(root->argv[1], "-") == 0)
        {
            if (env_find(env_list, "OLDPWD", -1))
            {
                if (chdir(oldpwd) == -1)
                    printf("error in changing directory\n");
                else
                    printf("%s\n", oldpwd);
                return ;
            }
            else
                printf("minishe v0.1: cd: OLDPWD not set\n");
            return ;
        }
        else 
        {
            if (chdir(root->argv[1]) == -1)
            {
                printf("cd: no such file or directory: %s\n", root->argv[1]);
                if (oldpwd)
                {
                    ft_list_remove_if(&env_list, "OLDPWD", &ft_strcmp);
                    add_back(&env_list, new_node(oldpwd, ft_strdup("OLDPWD"), 6));
                    return ;
                }
            }
            else if (oldpwd == NULL)
                add_back(&env_list, new_node(first_cwd, ft_strdup("OLDPWD"), 6));
        }
    }
    else 
        printf("cd: string not in pwd: %s\n", root->argv[1]);
}