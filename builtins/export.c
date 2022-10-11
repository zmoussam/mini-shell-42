/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/11 23:45:53 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

t_env_node	get_max_variable()
{
	t_env_node *head;
	t_env_node max;

	max.name = "";
	max.content = "";
	max.len = 0;
	head = env_list;
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
void	print_sort_list()
{
	t_env_node *head;
	t_env_node min;
	int *tmp;
	int k;

	min = get_max_variable();
	k = 0;
	if (env_list)
	{
			head = env_list;
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
			{
				if (min.content[0] == '\0')
					printf("declare -x %s\n", min.name);
				else if (min.content[0] == '\"')
					printf("declare -x %s=%s\n", min.name, min.content);
				else
					printf("declare -x %s=\"%s\"\n", min.name, min.content);
			}
			*tmp = -1;
	}
	if (k == 1)
		print_sort_list();
}

t_env_node *get_new_node(char *variable_with_content)
{
    int i;
    int len;
    int len2;
	char *content;
	char *name;
	
    len = ft_strlen(variable_with_content);
    i = 0;
    while (variable_with_content[i] != '=' && variable_with_content[i])
        i++;
	if (variable_with_content[i] == '\0')
	{
		content = (char *)malloc(1);
		content[0] = '\0';
		len2 = len;
	}
	else if(variable_with_content[i + 1] == '\0')
	{
		content = (char *)malloc(3);
		ft_strlcpy(content, "\"\"", 3);
		len2 = len - 1;
	}
	else
	{
    	content = (char *)malloc(sizeof(char) * \
		ft_strlen(&variable_with_content[i] + 1) + 1);
    	ft_strlcpy(content, &variable_with_content[i] + 1, \
		ft_strlen(&variable_with_content[i]) + 1);
    	len2 = len - ft_strlen(&variable_with_content[i]);
	}
    name = (char *)malloc(sizeof(char) * len2 + 1);
    ft_strlcpy(name, variable_with_content, len2 + 1);
    return (new_node(content, name, len2));
}

void	intialise_len_variable()
{
	t_env_node *head;
	
	head = env_list;
	while (head)
	{
		head->len = ft_strlen(head->name);
		head = head->next;	
	}
}
int	parss_variable(t_env_node *node)
{
	if ((node->name[0] <= 64 && (node->name[0] != '<' \
	&& node->name[0] != '>' && node->name[0] != ';')) \
	|| (node->name[0] == '[' || node->name[0] == ']' \
	|| node->name[0] == '{' || node->name[0] == '}' \
	|| node->name[0] == '~'))
	{
		if (node->name[0] == '-')
		{
			printf("minishell: export: %s: invalid option\n", node->name);
			printf("export: usage: export [name[=value] ...] or export \n");
		}
		else
		printf("minishell: export: `%s=%s': not a valid identifier\n", \
		node->name, node->content);
		return (1);
	}
		
	// printf("name[0] = %c\n", node->name[0]);
	return (0);
}
void	export(t_node *root)
{
	int i;
    t_env_node *new_env_node;
    
	i = 1;
	if (root->argc == 1 || (root->argc == 2 \
	&& (root->argv[1][0] == '#' || root->argv[1][0] == ';')))
	{
		print_sort_list();
		intialise_len_variable();
	}
    else 
    {
        while (root->argv[i])
        {
            new_env_node = get_new_node(root->argv[i]);
			// if (!new_node)
			// 	return ;
			if (parss_variable(new_env_node))
			{
				i++;
				free(new_env_node->name);
				free(new_env_node->content);
				free(new_env_node);
				continue;
			}
			else if (root->argv[i][0] == ';')
				break;
            add_back(&env_list, new_env_node);
            i++;
        }
    }
}