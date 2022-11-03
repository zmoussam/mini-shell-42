/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 20:58:19 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

t_env_list	get_max_variable(void)
{
	t_env_list	*head;
	t_env_list	max;

	max.name = "";
	max.content = "";
	max.len = 0;
	head = g_env_list;
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
t_env_list	get_min_variable(t_env_list max)
{
	t_env_list	*tmp;
	int			*tmp_len;

	tmp_len = NULL;
	tmp = g_env_list;
	while(tmp)
	{
		if (ft_strcmp(tmp->name, max.name) <= 0 && tmp->len != -1)
		{
			max = *tmp;
			tmp_len = &tmp->len;
		}
		tmp = tmp->next;
	}
	*tmp_len = -1;
	return (max);
}

void	print_sort_list()
{
	t_env_list	min;
	t_env_list	*tmp;
	t_env_list	max;

	max = get_max_variable();
	tmp = g_env_list;
	while(tmp)
	{
		min = get_min_variable(max);
		if (min.content[0] == '\0')
			printf("declare -x %s\n", min.name);
		else if (min.content[0] == '\"')
			printf("declare -x %s=%s\n", min.name, min.content);
		else
			printf("declare a-x %s=\"%s\"\n", min.name, min.content);
		tmp = tmp->next;
	}
}

t_env_list	*get_new_node(char *variable_with_content)
{
	int		i;
	int		len;
	int		len2;
	char	*content;

	len = ft_strlen(variable_with_content);
	len2 = len;
	i = 0;
	while (variable_with_content[i] != '=' && variable_with_content[i])
		i++;
	if (variable_with_content[i] == '\0')
		content = ft_strdup("");
	else if (variable_with_content[i + 1] == '\0')
	{
		content = ft_strdup("\"\"");
		len2 = len - 1;
	}
	else
	{
		content = ft_strdup(&variable_with_content[i] + 1);
		len2 = len - ft_strlen(&variable_with_content[i]);
	}
	return (new_node(content, \
	ft_substr(variable_with_content, 0, len2), len2));
}

void	intialise_len_variable(void)
{
	t_env_list *head;

	head = g_env_list;
	while (head)
	{
		head->len = ft_strlen(head->name);
		head = head->next;
	}
}
int	parss_variable(t_env_list *new_node)
{
	int		i;
	char	*tmp_content;
	char	*tmp_name;
	int		k;

	i = 0;
	if (ft_isdigit(new_node->name[0]))
	{
		printf("minishell: export: `%s=%s': not a valid identifier\n", \
			new_node->name, new_node->content);
		return (1);
	}
	k = 0;
	while (new_node->name[i])
	{
		if (new_node->name[i] == '+')
			k++;
		if (((new_node->name[i] <= 64 && !ft_isdigit(new_node->name[i])) \
			|| (new_node->name[i] >= 91 && new_node->name[i] <= 96 && new_node->name[i] != '_') \
			|| new_node->name[i] >= 123)
			&& new_node->name[new_node->len - 1] != '+')
		{
			if (new_node->name[0] == '-')
			{
				printf("minishell: export: %s: invalid option\n", \
					new_node->name);
				printf("export: usage: export [name[=value] ...] \
					or export \n");
			}
			else
				printf("minishell: export: `%s=%s': not a valid identifier\n", \
					new_node->name, new_node->content);
			return (1);
		}
		i++;
	}
	if (new_node->name[new_node->len - 1] == '+' && new_node->len != 1)
	{
		if (k > 1)
		{
			printf("minishell: export: `%s=%s': not a valid identifier\n", \
				new_node->name, new_node->content);
			return (1);
		}
		tmp_name = new_node->name;
		new_node->name = ft_strtrim(new_node->name, "+");
		free(tmp_name);
		if (env_find(g_env_list, new_node->name, -1) && new_node->content[0] != '\0')
		{
			tmp_content = new_node->content;
			new_node->content = ft_strjoin(env_find(g_env_list, new_node->name, -1)->content, new_node->content);
			free(tmp_content);
		}
	}
	return (0);
}

void	export(t_node *root)
{
	int			i;
	t_env_list	*new_node;

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
			new_node = get_new_node(root->argv[i]);
			if (!new_node)
				return ;
			if (parss_variable(new_node) == 1)
			{
				i++;
				free(new_node->name);
				free(new_node->content);
				free(new_node);
				continue ;
			}
			else if (root->argv[i][0] == ';')
				break ;
			if (env_find(g_env_list, new_node->name, -1))
				ft_list_remove_if(&g_env_list, new_node->name, &ft_strcmp);
			add_back(&g_env_list, new_node);
			i++;
		}
	}
}