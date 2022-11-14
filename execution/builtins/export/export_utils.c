/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:45:05 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/14 13:25:00 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

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

t_env_node	*get_new_node(char *variable_with_content, int index)
{
	int		len;
	int		len2;
	char	*content;

	len = ft_strlen(variable_with_content);
	len2 = len;
	while (variable_with_content[index] != '=' && variable_with_content[index])
		index++;
	if (variable_with_content[index] == '\0')
		content = ft_strdup("");
	else if (variable_with_content[index + 1] == '\0')
	{
		content = ft_strdup("\"\"");
		len2 = len - 1;
	}
	else
	{
		content = ft_strdup(&variable_with_content[index] + 1);
		len2 = len - ft_strlen(&variable_with_content[index]);
	}
	if (!content)
		return (NULL);
	return (new_node(content, \
	ft_substr(variable_with_content, 0, len2), len2));
}
