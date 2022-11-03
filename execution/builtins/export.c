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
t_env_list	get_min_variable(t_env_list min)
{
	t_env_list	*tmp;
	int			*tmp_len;

	tmp_len = NULL;
	tmp = g_env_list;
	while(tmp)
	{
		if (ft_strcmp(tmp->name, min.name) <= 0 && tmp->len != -1)
		{
			min = *tmp;
			tmp_len = &tmp->len;
		}
		tmp = tmp->next;
	}
	*tmp_len = -1;
	return (min);
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
	intialise_len_variable();
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
int	check_sign_plus(char *name, char *content)
{
	int i;
	int	c;

	i = 0;
	c = 0;
	while (name[i])
	{
		if (name[i] == '+')
			c++;
		i++;
	}
	if ((name[i - 1] == '+' && c > 1) || (name[i - 1] == '+' && content[0] == '\0'))
		return (1);
	else
		return (0);
}
int	check_special_char(char *name, char *content, int len)
{
	int i;

	i = 0;
	if (ft_isdigit(name[i]))
		return(printf("minishell: export: `%s=%s': not a valid identifier\n", \
		name, content));
	if (name[i] == '-')
		return (printf("minishell: export: %s: invalid option \nexport: usage: export [name[=value] ...] or export \n", name));
	if (check_sign_plus(name, content))
		return (printf("minishell: export: `%s': not a valid identifier\n", \
		name));
	while (name[i])
	{
		if (((name[i] <= 64 && !ft_isdigit(name[i])) \
		|| (name[i] >= 91 && name[i] <= 96 && name[i] != '_') \
		|| name[i] >= 123) && name[len - 1] != '+')
		return (printf("minishell: export: `%s=%s': not a valid identifier\n", \
		name, content));
		i++;
	}
	return (0);
}
int	parss_variable(t_env_list *node)
{
	int		i;
	char	*tmp_content;
	char	*tmp_name;
	int 	len;

	len = ft_strlen(node->name);
	i = 0;
	if (check_special_char(node->name, node->content, len))
		return (1);
	if (node->name[len - 1] == '+' && node->len != 1)
	{
		tmp_name = node->name;
		node->name = ft_strtrim(node->name, "+");
		free(tmp_name);
		if (env_find(g_env_list, node->name, -1) && node->content[0] != '\0' \
		&& ft_strcmp(node->content, "\"\""))
		{
			tmp_content = node->content;
			node->content = ft_strjoin(env_find(g_env_list, node->name, -1)->content, node->content);
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
		print_sort_list();
	else
	{
		while (root->argv[i])
		{
			if (root->argv[i][0] == ';')
				break ;
			new_node = get_new_node(root->argv[i]);
			if (!new_node)
				return ;
			if (parss_variable(new_node))
			{
				i++;
				delone_env(new_node);
				continue ;
			}
			if (env_find(g_env_list, new_node->name, -1))
				ft_list_remove_if(&g_env_list, new_node->name);
			add_back(&g_env_list, new_node);
			i++;
		}
	}
}