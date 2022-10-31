/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:42:14 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 20:55:28 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"
#include "env.h"

void	print_list(void)
{
	t_env_list	*head;

	head = g_env_list;
	while (head)
	{
		if (head->content[0] != '\0')
			printf("%s=%s\n", head->name, head->content);
		head = head->next;
	}
}

int	env_listsize(t_env_list *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	env_cmd(int argc)
{
	if (argc != 1)
		printf("use env with no options or arguments\n");
	else
		print_list();
}
