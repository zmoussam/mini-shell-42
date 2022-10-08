/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/08 10:13:07 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

typedef struct t_export_v
{
    char    *content;
    char    *name;
}t_export_v;

t_env_node	get_max_variable(t_env_node *env)
{
	t_env_node *head;
	t_env_node max;

	max.name = "";
	max.content = "";
	max.len = 0;
	head = env;
	while (head)
	{
		if (ft_strcmp(head->name, max.name) >= 0)
		{
			max.name = head->name;
			max.content = head->content;
		}
		head = head->next;
	}
	return (max);

}
void	print_sort_list(t_env_node *env)
{
	t_env_node *head;
	t_env_node min;
	int *tmp;
	int k;

	min = get_max_variable(env);
	k = 0;
	if (env)
	{
			head = env;
			while (head)
			{
				// printf("len = %d\n",head->len);
				if (ft_strcmp(head->name, min.name) <= 0 && head->len != -1)
				{
					min.name = head->name;
					min.content = head->content;
					tmp = &head->len;
					k = 1;
				}
				head = head->next;
			}
			if (k == 1)
				printf("%s=%s\n", min.name, min.content);
			*tmp = -1;
	}
	if (k == 1)
		print_sort_list(env);
}

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
    while(variable_with_content[i] != '=')
        i++;
    return_value->content = (char *)malloc(sizeof(char) * ft_strlen(&variable_with_content[i] + 1) + 1);
    ft_memcpy(return_value->content, &variable_with_content[i] + 1, ft_strlen(&variable_with_content[i] + 1) );
    len2 = len - ft_strlen(&variable_with_content[i]);
    return_value->name = (char *)malloc(sizeof(char) * len2 + 1);
    ft_memcpy(return_value->name, variable_with_content, len2);
    return_value->name[len2] = '\0';
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
		print_list(*env);
    else 
    {
        while (root->argv[i])
        {
            name_content = get_name_content(root->argv[i]);
            add_back(env, new_node(ft_strdup(name_content->content),ft_strdup(name_content->name), ft_strlen(name_content->name)));
            free(name_content->name);
            free(name_content->content);
            free(name_content);
            i++;
        }
    }
}