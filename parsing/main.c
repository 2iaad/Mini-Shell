char	*expand_env(char *line, t_env **env)
{
	int 	i;
	int		len;
	char	*new_line;
	char	*new;
	t_env	*tmp_env;
	t_env	*expander;
	int		var_len;

	i = 0;
	new = NULL;
	expander = NULL;
	while (line[i])
	{
		len = 0;
		while (line[i + len] != '\0' && line[i + len] != '$')
		{
			if (line[i + len] == '\'')
			{
				len++;
				while (line[i + len] && line[i + len] != '\'')
					len++;
				len++;
			}
			else
				len++;
		}
		if (len > 0) // if there is a string before the variable
		{
			new_line = ft_substr(line, i, len);
			new = ft_strjoin(new, new_line);
		}
		if (line[i + len] == '$' && line[i + len + 1] == '\0')
		{
			new = ft_strjoin(new, "$");
			i += len + 1;
		}
		else if (line[i + len] == '$' && ft_isnum(line[i + len + 1]))
		{
			var_len = 1;
			while(line[i + len + var_len] && ft_isnum(line[i + len + var_len]))
				var_len++;
			new_line = ft_substr(line, i + len + 2, var_len - 1);
			new = ft_strjoin(new, new_line);
			i += len + var_len;
		}
		else if (line[i + len] == '$')
		{
			var_len = 1;
			while(line[i + len + var_len] && !delimiters(line[i + len + var_len]))
				var_len++;
			tmp_env = *env;
			new_line = ft_substr(line, i + len + 1, var_len - 1);
			while (tmp_env)
			{
				if (ft_strcmp(tmp_env->variable, new_line) == 0)
				{
					expander = tmp_env;
					new = ft_strjoin(new, expander->value);
					break ;
				}
				tmp_env = tmp_env->next;
			}
			i += len + var_len;
		}
		else
			i += len;
	}
	printf("new = %s\n", new);
	return (new);
}