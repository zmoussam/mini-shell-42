/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:53:51 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/16 15:10:10 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <errno.h>

extern char	**environ;

char	*ft_getenv(const char *name)
{
	const size_t	len = ft_strlen(name);
	char			**env;

	if (!name || !len || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (NULL);
	}
	env = environ;
	while (*env)
	{
		if (ft_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
