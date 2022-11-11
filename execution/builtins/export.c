/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:53 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/11 18:06:29 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env_node	get_max_variable(void)
{
	t_env_node	*head;
	t_env_node	max;

	max.name = "";
	max.content = "";
	max.len = 0;
	head = g_lbv.list;
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

t_env_node	get_min_variable(t_env_node min)
{
	t_env_node	*tmp;
	int			*tmp_len;

	tmp_len = NULL;
	tmp = g_lbv.list;
	while (tmp)
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
	t_env_node	*head;

	head = g_lbv.list;
	while (head)
	{
		head->len = ft_strlen(head->name);
		head = head->next;
	}
}

void	print_sort_list(void)
{
	t_env_node	min;
	t_env_node	*tmp;
	t_env_node	max;

	max = get_max_variable();
	tmp = g_lbv.list;
	while (tmp)
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

t_env_node	*get_new_node(char *variable_with_content)
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
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (name[i])
	{
		if (name[i] == '+')
			c++;
		i++;
	}
	if ((name[i - 1] == '+' && c > 1) \
		|| (name[i - 1] == '+' && content[0] == '\0'))
		return (1);
	else
		return (0);
}

int	check_special_char(char *name, char *content, int len)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]))
		return (printf("minishell: export: `%s=%s': not a valid identifier\n", \
		name, content));
	if (name[i] == '-')
	{
		printf("minishell: export: %s: invalid option \n", name);
		return (printf("export: usage: export [name[=value]...] or export \n"));
	}
	if (check_sign_plus(name, content))
		return (printf("minishell: export: `%s': not a valid identifier\n", \
		name));
	while (name[i])
	{
		if (((name[i] <= 64 && !ft_isdigit(name[i])) \
		|| (name[i] >= 91 && name[i] <= 96 && name[i] != '_') \
		|| name[i] >= 123) && name[len - 1] != '+')
			return (printf("minishell: export: `%s=%s': ", name, content), \
				printf("not a valid identifier\n"));
		i++;
	}
	return (0);
}

int	parss_export_variable(t_env_node *node)
{
	t_env_node	*node_name;
	int			i;
	char		*tmp_content;
	char		*tmp_name;
	int			len;

	len = ft_strlen(node->name);
	i = 0;
	if (check_special_char(node->name, node->content, len))
		return (1);
	if (node->name[len - 1] == '+' && node->len != 1)
	{
		tmp_name = node->name;
		node->name = ft_strtrim(node->name, "+");
		node->len = ft_strlen(node->name);
		free(tmp_name);
		node_name = env_find(g_lbv.list, node->name, -1);
		if (node_name && node->content[0] != '\0' \
		&& ft_strcmp(node->content, "\"\""))
		{
			tmp_content = node->content;
			node->content = ft_strjoin(node_name->content, node->content);
			free(tmp_content);
		}
	}
	return (0);
}

int	remove_old_variable(t_env_node *new_node, int *i)
{
	if (!ft_strcmp(new_node->name, "PATH") && new_node->content[0] == '\0')
	{
		*i += 1;
		delone_env(new_node);
		return (1);
	}
	else
	{
		ft_list_remove_if(&g_lbv.list, new_node->name);
	}
	return (0);
}

void	add_export_variable(char **argv)
{
	t_env_node	*new_node;
	int			i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == ';' || argv[i][0] == '#')
			break ;
		new_node = get_new_node(argv[i]);
		if (!new_node)
			return ;
		if (parss_export_variable(new_node))
		{
			i++;
			delone_env(new_node);
			continue ;
		}
		if (env_find(g_lbv.list, new_node->name, ft_strlen(new_node->name)))
			if (remove_old_variable(new_node, &i))
				continue ;
		add_back(&g_lbv.list, new_node);
		i++;
	}
}

void	export(t_parser_node *root)
{
	if (root->ac == 1 || (root->ac == 2 \
		&& (root->av[1][0] == '#' || root->av[1][0] == ';')))
		print_sort_list();
	else
		add_export_variable(root->av);
}
