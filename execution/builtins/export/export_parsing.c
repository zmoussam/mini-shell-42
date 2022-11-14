/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:51:32 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/13 20:36:46 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

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

int	check_special_char(char *name, char *content, int len, int _option_error)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]))
		return (printf("minishell: export: `%s=%s': not a valid identifier\n", \
		name, content));
	if (name[i] == '-' && _option_error == 1)
	{
		printf("minishell: export: %s: invalid option \n", name);
		printf("export: usage: export [name[=value]...] or export \n");
		return (-1);
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

void	*concatenat_variable(t_env_node *node)
{
	t_env_node	*node_name;
	char		*tmp_name;
	char		*tmp_content;

	tmp_name = ft_strtrim(node->name, "+");
	if (!tmp_name)
		return (printf("minishell: memory was not allocated!!\n"), NULL);
	free(node->name);
	node->name = tmp_name;
	node->len = ft_strlen(node->name);
	node_name = env_find(g_lbv.list, node->name, -1);
	if (node_name && node->content[0] != '\0' \
	&& ft_strcmp(node->content, "\"\""))
	{
		tmp_content = ft_strjoin(node_name->content, node->content);
		if (!tmp_content)
			return (printf("minishell: memory was not allocated!!\n"), NULL);
		free(node->content);
		node->content = tmp_content;
	}
	return (NULL);
}

int	parss_export_variable(t_env_node *node, int _op_error)
{
	int			len;
	int			check_parse;

	len = ft_strlen(node->name);
	check_parse = check_special_char(node->name, node->content, len, _op_error);
	if (check_parse)
	{
		if (check_parse == -1)
			return (-1);
		g_lbv.exit_status = 256;
		return (1);
	}
	if (node->name[len - 1] == '+' && node->len != 1)
		concatenat_variable(node);
	return (0);
}
