/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zderfouf <zderfouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:14:56 by zderfouf          #+#    #+#             */
/*   Updated: 2024/08/01 11:29:24 by zderfouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_hidden(t_env **env, int flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (flag)
		{
			if (!ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)))
				tmp->hidden = true;
			if (!ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)))
				tmp->hidden = true;
		}
		else
		 	tmp->hidden = false;
		tmp = tmp->next;
	}
}

void	env_i(t_env **env, char **envp)
{
	int		i;
	char	**tmp;
	char	**str;

	i = 0;
	str = (char **) gv_coll (sizeof(char *) * 5);
	str[0] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	str[1] = ft_strdup("PWD=/Users/zderfouf/Desktop/minishell");
	str[2] = ft_strdup("SHLVL=1");
	str[3] = ft_strdup("_=/usr/bin/env");
	str[4] = NULL;
	while (str[i])
	{
		tmp = ft_split(str[i], '=');
		ft_lstadd_back(env, ft_lstnew(ft_strdup(tmp[0]), ft_strdup(tmp[1])));
		ft_free(tmp);
		i++;
	}
	ft_lstadd_back(env, ft_lstnew(ft_strdup("OLDPWD"), NULL));
	init_hidden(env, 1);
	ft_free(str);
	printf("\n");
}

void	init_env(t_env **env_list, char **env)
{
	int		i;
	char	**str;

	i = 0;
	*env_list = NULL;
	if (*env)
	{
		while (env[i])
		{
			str = ft_split(env[i], '=');
			if (!ft_strncmp(str[0], "OLDPWD", ft_strlen(str[0])))
			{
				ft_free(str);
				i++;
				continue;
			}
			ft_lstadd_back(env_list, ft_lstnew(ft_strdup(str[0]),
					ft_strdup(getenv(str[0]))));
			ft_free(str);
			i++;
		}
		init_hidden(env_list, 0);
	}
	else
		env_i(env_list, env);
}
