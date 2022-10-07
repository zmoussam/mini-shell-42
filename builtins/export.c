/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/07 19:37:10 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

typedef struct t_export_v
{
    char    *content;
    char    *name;
}t_export_v;

t_export_v *get_name_content(char *variable_with_content)
{
    int i;
    int len;
    int len2;
    t_export_v *return_value;
    return_value = (t_export_v *)malloc(sizeof(t_export_v));
    return_value->content = 0;
    return_value->name = 0;
    len = ft_strlen(variable_with_content);
    i = 0;
    while(i < len)
    {
        while(variable_with_content[i] != '=')
            i++;
        return_value->content = (char *)malloc(sizeof(char) * ft_strlen(&variable_with_content[i] + 1) + 1);
        ft_memcpy(return_value->content, &variable_with_content[i] + 1, ft_strlen(&variable_with_content[i] + 1) );
        len2 = len - ft_strlen(&variable_with_content[i]);
        return_value->name = (char *)malloc(sizeof(char) * len2 + 1);
        ft_memcpy(return_value->name, variable_with_content, len2);
        return_value->name[len2] = '\0';
        break;
    }
        // printf("name = %s\n", return_value->name);
        // printf("content = %s\n", return_value->content);
        // printf("lenn = %zu\n", ft_strlen(return_value->name));
        // printf("lenc = %zu\n", ft_strlen(return_value->content));
    return (return_value);
    
}
void	export(t_node *root, t_env_node **env)
{
	int i;
    t_export_v *name_content;
    
	i = 1;
	if (root->argc == 1)
		print_sort_list(*env);
    else 
    {
        while (root->argv[i])
        {
            name_content = get_name_content(root->argv[i]);
            add_back(env, new_node(name_content->content, name_content->name, ft_strlen(name_content->name)));
            free(name_content->content);
            free(name_content->name);
            free(name_content);
            // printf("env->name = %s\n", env->name);
            i++;
        }
    }
}