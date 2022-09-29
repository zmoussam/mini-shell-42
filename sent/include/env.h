/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 07:48:38 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/21 13:36:07 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

t_env	*env_init(const char *name, const char *value);
int		env_update(t_env *env, const char *value);
int		env_cmp(t_env *env1, t_env *env2);
void	env_destroy(t_env *env);

char	*sh_getenv(const char *name);
char	*sh_getenvn(const char *name, size_t n);
char	**sh_getenvp(void);
int		sh_setenv(const char *name, const char *value);
int		sh_unsetenv(const char *name);

#endif /* ENV_H */
