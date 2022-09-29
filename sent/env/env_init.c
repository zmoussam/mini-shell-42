/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:14:06 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 07:57:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

t_env	*env_init(const char *name, const char *value)
{
	t_env	*env;
	char	*name_dup;
	char	*value_dup;

	env = malloc(sizeof(t_env));
	name_dup = ft_strdup(name);
	value_dup = NULL;
	if (value)
		value_dup = ft_strdup(value);
	if (!env || !name || (value && !value_dup))
	{
		free(env);
		free(name_dup);
		free(value_dup);
		return (NULL);
	}
	env->name = name_dup;
	env->value = value_dup;
	return (env);
}
