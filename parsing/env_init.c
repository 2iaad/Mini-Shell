/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouram <ibouram@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:14:56 by zderfouf          #+#    #+#             */
/*   Updated: 2024/07/29 05:45:26 by ibouram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_i(t_env **env, char **envp)
{
	int		i;
	char	**tmp;
	char	**str;

	i = 0;
	str = (char **) malloc (sizeof(char *) * 5);
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
	ft_lstadd_back(env, ft_lstnew(ft_strdup("?"), ft_strdup("")));
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
			ft_lstadd_back(env_list, ft_lstnew(ft_strdup(str[0]),
					ft_strdup(getenv(str[0]))));
			ft_free(str);
			i++;
		}
		ft_lstadd_back(env_list, ft_lstnew(ft_strdup("?"), ft_strdup("")));
	}
	else
		env_i(env_list, env);
}
