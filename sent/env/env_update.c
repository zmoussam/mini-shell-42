/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:20:04 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/20 07:57:59 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

int	env_update(t_env *env, const char *value)
{
	char	*value_dup;

	if (env->value && !value)
		return (0);
	value_dup = NULL;
	if (value)
	{
		value_dup = ft_strdup(value);
		if (!value_dup)
			return (-1);
	}
	free(env->value);
	env->value = value_dup;
	return (0);
}
