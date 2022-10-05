/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/06 00:50:33 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void    add_new_variabl_to_env(t_env_node **env, t_env_node *new)
{
    t_env_node *head;
    t_env_node *tmp;
    
    if (env == NULL)
        add_back(env, new);
    else
    {
        if (ft_strcmp(new->name, (*env)->name) < 0)
        {
            if (new)
	        {
		        new->next = *env;
		        *env = new;
            }
            return ;
        }
        head = *env;
        while (*env)
        {
            if (ft_strcmp(new->name, (*env)->name) > 0)
            {
                tmp = *env;
                *env = (*env)->next;
            }
            else
            {
                 tmp->next = new;
                 new->next = *env;
                 return ;
            }   
        }
    }
}
typedef struct t_export_v
{
    char    *content;
    char    *name;
}t_export_v;

t_export_v get_name_content(char *variable_with_content)
{
    int i;
    int len;
    int len2;
    t_export_v return_value;
    return_value.content = 0;
    return_value.name = 0;
    len = ft_strlen(variable_with_content);
    i = 0;
    while(i < len)
    {
        while(variable_with_content[i] != '=')
            i++;
        return_value.content = &variable_with_content[i] + 1;
        len2 = len - ft_strlen(&variable_with_content[i]);
        return_value.name = (char *)malloc(sizeof(char) * len2 + 1);
        ft_memcpy(return_value.name, variable_with_content, len2);
        return_value.name[len2] = '\0';
        printf("name = %s\n", return_value.name);
        printf("content = %s\n", return_value.content);
        printf("lenn = %zu\n", ft_strlen(return_value.name));
        printf("lenc = %zu\n", ft_strlen(return_value.content));
        break;
    }
    return (return_value);
    
}
void	export(t_node *root, t_env_node *env)
{
	int i;
    t_export_v name_content;
    
	i = 1;
	if (root->argc == 1)
		print_list(env);
    else 
    {
        while (root->argv[i])
        {
            name_content = get_name_content(root->argv[i]);
            add_new_variabl_to_env(&env, new_node(name_content.content, \
            name_content.name, ft_strlen(name_content.name)));
            i++;
        }
    }
}